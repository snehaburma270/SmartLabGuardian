#include "SemaphoreManager.h"

#include <sys/ipc.h>
#include <sys/sem.h>
#include <iostream>

union Semun {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
};

SemaphoreManager::SemaphoreManager()
    : semid(-1) {
}

SemaphoreManager::~SemaphoreManager() {
    if (semid != -1) {
        semctl(semid, 0, IPC_RMID);
    }
}

bool SemaphoreManager::create() {
    key_t key = 5678;

    semid = semget(key, 1, IPC_CREAT | 0666);

    if (semid == -1) {
        std::cerr << "[-] Failed to create semaphore.\n";
        return false;
    }

    Semun value;
    value.val = 1;

    if (semctl(semid, 0, SETVAL, value) == -1) {
        std::cerr << "[-] Failed to initialize semaphore.\n";
        return false;
    }

    std::cout << "[+] Semaphore created successfully.\n";

    return true;
}

bool SemaphoreManager::wait() {
    if (semid == -1) {
        return false;
    }

    struct sembuf operation;
    operation.sem_num = 0;
    operation.sem_op = -1;
    operation.sem_flg = 0;

    return semop(semid, &operation, 1) != -1;
}

bool SemaphoreManager::signal() {
    if (semid == -1) {
        return false;
    }

    struct sembuf operation;
    operation.sem_num = 0;
    operation.sem_op = 1;
    operation.sem_flg = 0;

    return semop(semid, &operation, 1) != -1;
}

