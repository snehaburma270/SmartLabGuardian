#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

// Represents a lab machine and a singly linked list node
struct Computer {
    std::string id;          // e.g., "LAB-PC-01"
    std::string ipAddress;   // e.g., "192.168.1.101"
    std::string location;    // e.g., "Lab-A"
    double cpuUsage;         // Percentage (0.0 - 100.0)
    double ramUsage;         // Percentage (0.0 - 100.0)
    double diskUsage;        // Percentage (0.0 - 100.0)
    int temperature;         // Simulated hardware sensor reading (°C)
    bool isOnline;

    Computer* next;          // Pointer to next node in the linked list

    // Constructor to initialize default node values
    Computer(std::string id_, std::string ip_, std::string loc_)
        : id(id_), ipAddress(ip_), location(loc_),
          cpuUsage(0.0), ramUsage(0.0), diskUsage(0.0),
          temperature(42), isOnline(true), next(nullptr) {}
};

#endif