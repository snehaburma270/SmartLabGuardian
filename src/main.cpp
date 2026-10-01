#include "LabManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void showMenu() {
    std::cout << "\n============================================\n"
              << "       SMARTLAB GUARDIAN MONITORING         \n"
              << "============================================\n"
              << "1. Scan & Update Node Health (Telemetry/Proc)\n"
              << "2. Request a Computer\n"
              << "3. Release a Computer\n"
              << "4. View All Registered Monitored Computers\n"
              << "5. Search Computer by ID (Linear Search)\n"
              << "6. Sort Nodes by CPU Utilization (Bubble Sort)\n"
              << "7. Dispatch Highest Priority Task (Heap Queue)\n"
              << "8. Check Linux Device Driver\n"
              << "9. Exit Application\n"
              << "Enter choice: ";
}

void checkLinuxDevice()
{
    std::ifstream device("/dev/smartlab");

    if (!device.is_open())
    {
        std::cout << "\nLinux Device Driver Status\n";
        std::cout << "--------------------------\n";
        std::cout << "SmartLab character device is not available.\n";
        std::cout << "Expected device: /dev/smartlab\n";
        std::cout << "The driver can be loaded on a compatible Linux kernel.\n";
        return;
    }

    std::string message;
    std::getline(device, message);

    device.close();

    std::cout << "\nLinux Device Driver Status\n";
    std::cout << "--------------------------\n";
    std::cout << message << "\n";
}

int main() {

    if (!fs::exists("data")) {
        fs::create_directories("data");
    }

    LabManager lab;

    lab.addComputer("LAB-PC-01", "192.168.1.101", "Lab-A");
    lab.addComputer("LAB-PC-02", "192.168.1.102", "Lab-A");
    lab.addComputer("LAB-PC-03", "192.168.1.103", "Lab-B");
    lab.addComputer("LAB-PC-04", "192.168.1.104", "Lab-B");

    int choice = 0;

    while (choice != 9) {

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
                lab.requestComputer();
                break;

            case 3:
                lab.releaseComputer();
                break;

            case 4:
                lab.displayComputers();
                break;

            case 5: {
                std::cout << "\nEnter Computer ID: ";

                std::string id;
                std::cin >> id;

                Computer* found = lab.findComputer(id);

                if (found) {
                    std::cout << "\n[+] Computer Found\n";
                    std::cout << "    ID          : " << found->id << "\n";
                    std::cout << "    IP Address  : " << found->ipAddress << "\n";
                    std::cout << "    Location    : " << found->location << "\n";
                    std::cout << "    CPU Usage   : " << found->cpuUsage << "%\n";
                    std::cout << "    RAM Usage   : " << found->ramUsage << "%\n";
                    std::cout << "    Disk Usage  : " << found->diskUsage << "%\n";
                    std::cout << "    Temperature : " << found->temperature << " C\n";
                    std::cout << "    Status      : "
                              << (found->isOnline ? "ONLINE" : "OFFLINE")
                              << "\n";
                    std::cout << "    Availability: "
                              << found->availability << "\n";
                }
                else {
                    std::cout << "\n[-] Computer ID not found.\n";
                }

                break;
            }

            case 6:
                lab.sortAndDisplayByCpu();
                break;

            case 7:
                lab.processNextMaintenanceTask();
                break;

            case 8:
                checkLinuxDevice();
                break;

            case 9:
                std::cout << "\nShutting down SmartLab Guardian.\n";
                std::cout << "System logs are saved in the data folder.\n";
                break;

            default:
                std::cout << "\nInvalid choice. "
                          << "Please enter a number between 1 and 9.\n";
        }
    }

    return 0;
}
