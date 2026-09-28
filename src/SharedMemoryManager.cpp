#include "SharedMemoryManager.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <iostream>

SharedMemoryManager::SharedMemoryManager()
    : shmid(-1), sharedData(nullptr) {
}

SharedMemoryManager::~SharedMemoryManager() {
    detach();
}

bool SharedMemoryManager::create() {
    // Create a shared memory segment
    key_t key = 1234;

shmid = shmget(key, sizeof(SharedLabStatus),
               IPC_CREAT | 0666);

    if (shmid == -1) {
        std::cerr << "[-] Failed to create shared memory.\n";
        return false;
    }

    // Attach shared memory to this process
    sharedData = static_cast<SharedLabStatus*>(
        shmat(shmid, nullptr, 0)
    );

    if (sharedData == reinterpret_cast<void*>(-1)) {
        sharedData = nullptr;
        std::cerr << "[-] Failed to attach shared memory.\n";
        return false;
    }

    std::memset(sharedData, 0, sizeof(SharedLabStatus));

    std::cout << "[+] Shared memory created successfully.\n";

    return true;
}

bool SharedMemoryManager::writeStatus(
    const std::string& id,
    const std::string& ip,
    const std::string& location,
    double cpu,
    double ram,
    double disk,
    int temperature,
    bool online) {

    if (sharedData == nullptr) {
        return false;
    }

    std::strncpy(sharedData->computerId,
                 id.c_str(),
                 sizeof(sharedData->computerId) - 1);

    std::strncpy(sharedData->ipAddress,
                 ip.c_str(),
                 sizeof(sharedData->ipAddress) - 1);

    std::strncpy(sharedData->location,
                 location.c_str(),
                 sizeof(sharedData->location) - 1);

    sharedData->cpuUsage = cpu;
    sharedData->ramUsage = ram;
    sharedData->diskUsage = disk;
    sharedData->temperature = temperature;
    sharedData->isOnline = online ? 1 : 0;

    return true;
}

void SharedMemoryManager::detach() {
    if (sharedData != nullptr) {
        shmdt(sharedData);
        sharedData = nullptr;
    }

    if (shmid != -1) {
        shmctl(shmid, IPC_RMID, nullptr);
        shmid = -1;
    }
}

