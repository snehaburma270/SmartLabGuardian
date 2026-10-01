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
LabManager::LabManager() : head(nullptr), nextTaskId(1), nextAlertId(101) {
    sharedMemory.create();
    semaphore.create();
    tcpServer.start(5000);
}

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
              << std::setw(8)  << "State"
              << std::setw(12) << "Availability\n";

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
                  << std::setw(8) << (temp->isOnline ? "ONLINE" : "OFFLINE")
                  << std::setw(12) << temp->availability
                  << "\n";

        temp = temp->next;
    }

    std::cout << "==================================================================================\n";
}
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

    bool faultDetected = false;

    if (computer->diskUsage > 90.0) {
        taskQueue.push({
            nextTaskId++,
            computer->id,
            "Disk capacity breached 90%",
            Severity::CRITICAL
        });

        logEvent("CRITICAL: Disk capacity exceeded on " + computer->id);
        faultDetected = true;
    }

    if (computer->temperature > 82) {
        taskQueue.push({
            nextTaskId++,
            computer->id,
            "Thermal runaway detected (>82C)",
            Severity::CRITICAL
        });

        logEvent("CRITICAL: Overheating reported on " + computer->id);
        faultDetected = true;
    }

    if (computer->ramUsage > 80.0) {
        taskQueue.push({
            nextTaskId++,
            computer->id,
            "RAM consumption high (>80%)",
            Severity::HIGH
        });

        logEvent("HIGH: High memory usage on " + computer->id);
        faultDetected = true;
    }

    if (computer->cpuUsage > 75.0) {
        taskQueue.push({
            nextTaskId++,
            computer->id,
            "High CPU load (>75%)",
            Severity::MEDIUM
        });

        logEvent("MEDIUM: CPU threshold breached on " + computer->id);
        faultDetected = true;
    }

    if (faultDetected) {
        computer->availability = "FAULTY";

        std::cout << "[!] " << computer->id
                  << " marked as FAULTY.\n";

        logEvent("FAULTY: " + computer->id +
                 " marked unavailable due to detected fault.");
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

        // Store the latest computer status in shared memory
        semaphore.wait();

        sharedMemory.writeStatus(
          temp->id,
          temp->ipAddress,
          temp->location,
          temp->cpuUsage,
          temp->ramUsage,
          temp->diskUsage,
          temp->temperature,
          temp->isOnline
          );

          semaphore.signal();

        std::string message =
            "Computer: " + temp->id +
            " | CPU: " + std::to_string(temp->cpuUsage) + "%" +
            " | RAM: " + std::to_string(temp->ramUsage) + "%" +
            " | Disk: " + std::to_string(temp->diskUsage) + "%";

         tcpServer.sendStatus(message);
         udpClient.sendMessage(
               message,
               "127.0.0.1",
                5001
);

temp = temp->next;
    }

    std::cout << "\n[+] Network scan complete. All nodes evaluated and priority queue updated.\n";
}



// Pops the highest-priorit ticket from the Priority Queue
void LabManager::processNextMaintenanceTask() {
    if (taskQueue.empty()) {
        std::cout << "\n[i] Priority Queue is empty. No tasks to dispatch.\n";
        return;
    }

    MaintenanceTask top = taskQueue.top();
    taskQueue.pop();

    std::string priorityText;

    switch (top.priority) {
    case Severity::CRITICAL:
        priorityText = "CRITICAL";
        break;

    case Severity::HIGH:
        priorityText = "HIGH";
        break;

    case Severity::MEDIUM:
        priorityText = "MEDIUM";
        break;

    case Severity::LOW:
        priorityText = "LOW";
        break;
}

    std::cout << "\nTask ID    : " << top.taskId << "\n"
              << "Target Node: " << top.computerId << "\n"
              << "Priority   : [" << priorityText << "]\n"
              << "Issue      : " << top.issue << "\n";

    logEvent("Dispatched task ID " +
             std::to_string(top.taskId) +
             " on " + top.computerId);
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
void LabManager::requestComputer() {
    double requiredRam;
    double maximumCpu;

    std::cout << "\nEnter minimum RAM required (%): ";
    std::cin >> requiredRam;

    std::cout << "Enter maximum acceptable CPU usage (%): ";
    std::cin >> maximumCpu;

    Computer* temp = head;

    while (temp != nullptr) {

        double availableRam = 100.0 - temp->ramUsage;

        if (temp->availability == "AVAILABLE" &&
            temp->isOnline &&
            availableRam >= requiredRam &&
            temp->cpuUsage <= maximumCpu) {

            temp->availability = "ASSIGNED";

            std::cout << "\n[+] Computer Assigned Successfully\n";
            std::cout << "Computer: " << temp->id << "\n";
            std::cout << "IP Address: " << temp->ipAddress << "\n";
            std::cout << "Location: " << temp->location << "\n";
            std::cout << "Available RAM: " << availableRam << "%\n";
            std::cout << "Current CPU Usage: " << temp->cpuUsage << "%\n";

            return;
        }

        temp = temp->next;
    }

    std::cout << "\n[-] No suitable computer is available.\n";
}

void LabManager::releaseComputer() {
    std::string id;

    std::cout << "\nEnter Computer ID to release: ";
    std::cin >> id;

    Computer* temp = head;

    while (temp != nullptr) {

        if (temp->id == id) {

            if (temp->availability == "ASSIGNED") {

                temp->availability = "AVAILABLE";

                std::cout << "\n[+] Computer Released Successfully\n";
                std::cout << "Computer: " << temp->id << "\n";
                std::cout << "IP Address: " << temp->ipAddress << "\n";
                std::cout << "Location: " << temp->location << "\n";
                std::cout << "Availability: " << temp->availability << "\n";

                return;
            }

            if (temp->availability == "FAULTY") {
                std::cout << "\n[-] Computer is marked as FAULTY.\n";
                std::cout << "It cannot be released as an available computer.\n";
                return;
            }

            std::cout << "\n[-] Computer is not currently assigned.\n";
            return;
        }

        temp = temp->next;
    }

    std::cout << "\n[-] Computer ID not found.\n";
}
