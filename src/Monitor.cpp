#include "Monitor.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#ifdef __linux__
#include <unistd.h>
#include <sys/statvfs.h>
#endif

// CPU Metric: Reads /proc/stat on Linux, simulates on Windows
double Monitor::getHostCpuUsage() {
#ifdef __linux__
    std::ifstream file("/proc/stat");
    if (file.is_open()) {
        std::string cpu;
        long user, nice, system, idle, iowait, irq, softirq, steal;
        file >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
        file.close();

        long totalIdle = idle + iowait;
        long totalActive = user + nice + system + irq + softirq + steal;
        long total = totalIdle + totalActive;

        if (total > 0) {
            return (static_cast<double>(totalActive) / total) * 100.0;
        }
    }
#endif
    return 35.0 + (rand() % 45); // Dynamic fallback
}

// RAM Metric: Reads /proc/meminfo on Linux, simulates on Windows
double Monitor::getHostRamUsage() {
#ifdef __linux__
    std::ifstream file("/proc/meminfo");
    if (file.is_open()) {
        std::string key;
        long memTotal = 0, memAvailable = 0, value;
        std::string unit;

        while (file >> key >> value >> unit) {
            if (key == "MemTotal:") memTotal = value;
            else if (key == "MemAvailable:") memAvailable = value;
            if (memTotal && memAvailable) break;
        }
        file.close();

        if (memTotal > 0) {
            return (static_cast<double>(memTotal - memAvailable) / memTotal) * 100.0;
        }
    }
#endif
    return 48.0 + (rand() % 40);
}

// Disk Metric: Uses statvfs() on Linux, simulates on Windows
double Monitor::getHostDiskUsage(const std::string& path) {
#ifdef __linux__
    struct statvfs stat;
    if (statvfs(path.c_str(), &stat) == 0) {
        unsigned long long total = stat.f_blocks * stat.f_frsize;
        unsigned long long free = stat.f_bfree * stat.f_frsize;
        if (total > 0) {
            return (static_cast<double>(total - free) / total) * 100.0;
        }
    }
#else
    (void)path;
#endif
    return 55.0 + (rand() % 40);
}

void Monitor::pollLabNode(Computer* comp) {
    if (!comp) return;

    if (comp->id == "LAB-PC-01") {
        comp->cpuUsage = getHostCpuUsage();
        comp->ramUsage = getHostRamUsage();
        comp->diskUsage = getHostDiskUsage("/");
        comp->temperature = 42 + static_cast<int>(comp->cpuUsage / 3.0);
    } else {
        comp->cpuUsage = 20.0 + (rand() % 75);
        comp->ramUsage = 35.0 + (rand() % 60);
        comp->diskUsage = 40.0 + (rand() % 58);
        comp->temperature = 38 + (rand() % 52); 
    }
    comp->isOnline = true;
}