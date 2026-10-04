#ifndef MAINTENANCE_TASK_H
#define MAINTENANCE_TASK_H

#include "Alert.h"
#include <string>


struct MaintenanceTask {
    int taskId;
    std::string computerId;
    std::string issue;
    Severity priority;

    
    bool operator<(const MaintenanceTask& other) const {
        return static_cast<int>(this->priority) < static_cast<int>(other.priority);
    }
};

#endif
