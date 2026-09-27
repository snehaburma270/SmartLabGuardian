#ifndef ALERT_H
#define ALERT_H

#include <string>

// Enum class defining fault severity levels
enum class Severity { 
    LOW = 1, 
    MEDIUM = 2, 
    HIGH = 3, 
    CRITICAL = 4 
};

// Represents a recorded alert entry
struct Alert {
    int alertId;
    std::string computerId;
    std::string description;
    Severity severity;
    std::string timestamp;
};

#endif