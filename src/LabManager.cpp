#include "LabManager.h"
#include "Monitor.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>

// Constructor initializes empty list and IDs
LabManager::LabManager() : head(nullptr), nextTaskId(1), nextAlertId(101) {}

// Destructor traverses the linked list and frees dynamic memory
LabManager::~LabManager() {
    Computer* current = head;
    while (current != nullptr) {
        Computer* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

// Logs events with timestamps to data/system_log.txt
void LabManager::logEvent(const std::string& message) {
    int fd = open("data/system_log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1) {
        return;
    }

    // Lock the log file before writing
    if (flock(fd, LOCK_EX) == -1) {
        close(fd);
        return;
    }

    std::time_t now = std::time(nullptr);
    char buf[26];

#if defined(_WIN32) || defined(_WIN64)
    ctime_s(buf, sizeof(buf), &now);
#else
    ctime_r(&now, buf);
#endif

    buf[24] = '\0';

    std::string logMessage =
        "[" + std::string(buf) + "] " + message + "\n";

    write(fd, logMessage.c_str(), logMessage.size());

    // Unlock after writing
    flock(fd, LOCK_UN);

    close(fd);
}

// Linked List Operation: Insert at end
void LabManager::addComputer(const std::string& id, const std::string& ip, const std::string& loc) {
    Computer* newComp = new Computer(id, ip, loc);

    if (head == nullptr) {
        head = newComp;
    } else {
        Computer* temp = head;

        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newComp;
    }

    logEvent("Registered Node: " + id + " at IP: " + ip);
}

// Linked List Operation: Traversal and display
void LabManager::displayComputers() const {
    std::cout << "\n================================ LAB NODES STATUS ================================\n";

    std::cout << std::left
              << std::setw(12) << "ID"
              << std::setw(16) << "IP Address"
              << std::setw(10) << "Location"
              << std::setw(10) << "CPU(%)"
              << std::setw(10) << "RAM(%)"
              << std::setw(10) << "Disk(%)"
              << std::setw(10) << "Temp(C)"
              << std::setw(8)  << "State\n";

    std::cout << "----------------------------------------------------------------------------------\n";

    Computer* temp = head;

    while (temp != nullptr) {
        std::cout << std::left
                  << std::setw(12) << temp->id
                  << std::setw(16) << temp->ipAddress
                  << std::setw(10) << temp->location
                  << std::setw(10) << std::fixed << std::setprecision(1) << temp->cpuUsage
                  << std::setw(10) << temp->ramUsage
                  << std::setw(10) << temp->diskUsage
                  << std::setw(10) << temp->temperature
                  << (temp->isOnline ? "ONLINE" : "OFFLINE") << "\n";

        temp = temp->next;
    }

    std::cout << "==================================================================================\n";
}

// Linear Search across dynamic linked nodes
Computer* LabManager::findComputer(const std::string& id) {
    Computer* temp = head;

    while (temp != nullptr) {
        if (temp->id == id) {
            return temp; // Match found
        }

        temp = temp->next;
    }

    return nullptr; // Not found
}

// Fault Detection Module
// Evaluates the health values of a single computer
void LabManager::evaluateFaults(Computer* computer) {

    if (computer->diskUsage > 90.0) {
        taskQueue.push({
            nextTaskId++,
            computer->id,
            "Disk capacity breached 90%",
            Severity::CRITICAL
        });

        logEvent("CRITICAL: Disk capacity exceeded on " + computer->id);

    } else if (computer->temperature > 82) {
        taskQueue.push({
            nextTaskId++,
            computer->id,
            "Thermal runaway detected (>82C)",
            Severity::CRITICAL
        });

        logEvent("CRITICAL: Overheating reported on " + computer->id);

    } else if (computer->ramUsage > 80.0) {
        taskQueue.push({
            nextTaskId++,
            computer->id,
            "RAM consumption high (>80%)",
            Severity::HIGH
        });

        logEvent("HIGH: High memory usage on " + computer->id);

    } else if (computer->cpuUsage > 75.0) {
        taskQueue.push({
            nextTaskId++,
            computer->id,
            "High CPU load (>75%)",
            Severity::MEDIUM
        });

        logEvent("MEDIUM: CPU threshold breached on " + computer->id);
    }
}

// Monitors all nodes and evaluates their health
void LabManager::scanNetworkAndEvaluate() {
    Computer* temp = head;

    while (temp != nullptr) {

        // Collect current health information
        Monitor::pollLabNode(temp);

        // Evaluate the collected health information
        evaluateFaults(temp);

        temp = temp->next;
    }

    std::cout << "\n[+] Network scan complete. All nodes evaluated and priority queue updated.\n";
}

// Pops the highest-priority ticket from the Priority Queue
void LabManager::processNextMaintenanceTask() {
    if (taskQueue.empty()) {
        std::cout << "\n[i] Priority Queue is empty. No tasks to dispatch.\n";
        return;
    }

    MaintenanceTask top = taskQueue.top();
    taskQueue.pop();

    std::string sevStr;

    switch (top.priority) {
        case Severity::CRITICAL:
            sevStr = "CRITICAL";
            break;

        case Severity::HIGH:
            sevStr = "HIGH";
            break;

        case Severity::MEDIUM:
            sevStr = "MEDIUM";
            break;

        case Severity::LOW:
            sevStr = "LOW";
            break;
    }

    std::cout << "\n================ DISPATCHING TASK ================\n"
              << "Task ID    : " << top.taskId << "\n"
              << "Target Node: " << top.computerId << "\n"
              << "Priority   : [" << sevStr << "]\n"
              << "Issue      : " << top.issue << "\n"
              << "Status     : Dispatched to Lab Sysadmin.\n"
              << "==================================================\n";

    logEvent("Dispatched task ID " +
             std::to_string(top.taskId) +
             " on " +
             top.computerId);
}

// Bubble Sort demonstration on node pointers
void LabManager::sortAndDisplayByCpu() {
    std::vector<Computer*> arr;

    Computer* curr = head;

    while (curr != nullptr) {
        arr.push_back(curr);
        curr = curr->next;
    }

    int n = static_cast<int>(arr.size());

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j]->cpuUsage < arr[j + 1]->cpuUsage) {
                // Sort descending
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }

    std::cout << "\n--- COMPUTERS SORTED BY CPU LOAD (DESCENDING) ---\n";

    for (auto c : arr) {
        std::cout << c->id
                  << " | CPU: "
                  << std::fixed
                  << std::setprecision(1)
                  << c->cpuUsage
                  << "% | RAM: "
                  << c->ramUsage
                  << "% | IP: "
                  << c->ipAddress
                  << "\n";
    }
}
