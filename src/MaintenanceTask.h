#ifndef MAINTENANCE_TASK_H
#define MAINTENANCE_TASK_H

#include "Alert.h"
#include <string>

// Encapsulates actionable maintenance tasks prioritized in a Priority Queue
struct MaintenanceTask {
    int taskId;
    std::string computerId;
    std::string issue;
    Severity priority;

    // Overload the '<' operator so std::priority_queue orders highest severity first
    bool operator<(const MaintenanceTask& other) const {
        return static_cast<int>(this->priority) < static_cast<int>(other.priority);
    }
};

#endif