#ifndef LAB_MANAGER_H
#define LAB_MANAGER_H

#include "Computer.h"
#include "Alert.h"
#include "MaintenanceTask.h"
#include <queue>
#include <vector>
#include <string>

class LabManager {
private:
    Computer* head;                                 // Pointer to start of Singly Linked List
    std::priority_queue<MaintenanceTask> taskQueue; // C++ STL Priority Queue (Heap)
    int nextTaskId;
    int nextAlertId;

    void logEvent(const std::string& message);
    void evaluateFaults(Computer* computer);        // Fault Detection Module

public:
    LabManager();
    ~LabManager(); // Destructor: Frees all heap memory used by linked list

    // Core Member Functions
    void addComputer(const std::string& id, const std::string& ip, const std::string& loc);
    void displayComputers() const;
    Computer* findComputer(const std::string& id); // Linear Search
    void scanNetworkAndEvaluate();                 // Monitoring & fault evaluation
    void processNextMaintenanceTask();             // Highest priority dispatch
    void sortAndDisplayByCpu();                    // Bubble Sort
};

#endif