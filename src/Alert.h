#ifndef ALERT_H
#define ALERT_H

#include <string>

enum class Severity { 
    LOW = 1, 
    MEDIUM = 2, 
    HIGH = 3, 
    CRITICAL = 4 
};

struct Alert {
    int alertId;
    std::string computerId;
    std::string description;
    Severity severity;
    std::string timestamp;
};

#endif
