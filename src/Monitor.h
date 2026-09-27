#ifndef MONITOR_H
#define MONITOR_H

#include "Computer.h"
#include <string>

class Monitor {
public:
    static double getHostCpuUsage();
    static double getHostRamUsage();
    static double getHostDiskUsage(const std::string& path = "/");
    static void pollLabNode(Computer* comp);
};

#endif