#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>

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

int main() {
    key_t key = 1234;

    int shmid = shmget(key, sizeof(SharedLabStatus), 0666);

    if (shmid == -1) {
        std::cout << "[-] Shared memory not found.\n";
        return 1;
    }

    SharedLabStatus* data =
        static_cast<SharedLabStatus*>(shmat(shmid, nullptr, 0));

    if (data == reinterpret_cast<void*>(-1)) {
        std::cout << "[-] Failed to attach to shared memory.\n";
        return 1;
    }

    std::cout << "\n========== SHARED MEMORY READER ==========\n";
    std::cout << "Computer ID : " << data->computerId << "\n";
    std::cout << "IP Address  : " << data->ipAddress << "\n";
    std::cout << "Location    : " << data->location << "\n";
    std::cout << "CPU Usage   : " << data->cpuUsage << "%\n";
    std::cout << "RAM Usage   : " << data->ramUsage << "%\n";
    std::cout << "Disk Usage  : " << data->diskUsage << "%\n";
    std::cout << "Temperature : " << data->temperature << " C\n";
    std::cout << "Online      : " << (data->isOnline ? "YES" : "NO") << "\n";

    shmdt(data);

    return 0;
}
