#include "LabManager.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void showMenu() {
    std::cout << "\n============================================\n"
              << "       SMARTLAB GUARDIAN MONITORING         \n"
              << "============================================\n"
              << "1. Scan & Update Node Health (Telemetry/Proc)\n"
              << "2. View All Registered Monitored Computers\n"
              << "3. Search Computer by ID (Linear Search)\n"
              << "4. Sort Nodes by CPU Utilization (Bubble Sort)\n"
              << "5. Dispatch Highest Priority Task (Heap Queue)\n"
              << "6. Exit Application\n"
              << "Enter choice: ";
}

int main() {
    // Standard C++17: Ensure the data directory exists for logging
    if (!fs::exists("data")) {
        fs::create_directories("data");
    }

    LabManager lab;

    // Seed initial nodes into the dynamic singly linked list
    lab.addComputer("LAB-PC-01", "192.168.1.101", "Lab-A");
    lab.addComputer("LAB-PC-02", "192.168.1.102", "Lab-A");
    lab.addComputer("LAB-PC-03", "192.168.1.103", "Lab-B");
    lab.addComputer("LAB-PC-04", "192.168.1.104", "Lab-B");

    int choice = 0;
    while (choice != 6) {
        showMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                lab.scanNetworkAndEvaluate();
                break;
            case 2:
                lab.displayComputers();
                break;
            case 3: {
                std::cout << "Enter Computer ID (e.g., LAB-PC-01): ";
                std::string id;
                std::cin >> id;
                Computer* found = lab.findComputer(id);
                if (found) {
                    std::cout << "\n[+] Record Found in Linked List:\n"
                              << "    ID       : " << found->id << "\n"
                              << "    IP       : " << found->ipAddress << "\n"
                              << "    Location : " << found->location << "\n"
                              << "    CPU      : " << found->cpuUsage << "%\n"
                              << "    RAM      : " << found->ramUsage << "%\n";
                } else {
                    std::cout << "[-] Node ID not found in system.\n";
                }
                break;
            }
            case 4:
                lab.sortAndDisplayByCpu();
                break;
            case 5:
                lab.processNextMaintenanceTask();
                break;
            case 6:
                std::cout << "Shutting down SmartLab Guardian. Data saved.\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    }
    return 0;
}