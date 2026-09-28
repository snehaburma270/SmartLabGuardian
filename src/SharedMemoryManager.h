#ifndef SHARED_MEMORY_MANAGER_H
#define SHARED_MEMORY_MANAGER_H

#include <string>

struct SharedLabStatus {
    char computerId[20];
    char ipAddress[20];
    char location[20];

    double cpuUsage;
    double ramUsage;
    double diskUsage;

    int temperature;
    int isOnline;
};

class SharedMemoryManager {
private:
    int shmid;
    SharedLabStatus* sharedData;

public:
    SharedMemoryManager();
    ~SharedMemoryManager();

    bool create();
    bool writeStatus(const std::string& id,
                     const std::string& ip,
                     const std::string& location,
                     double cpu,
                     double ram,
                     double disk,
                     int temperature,
                     bool online);

    void detach();
};

#endif
