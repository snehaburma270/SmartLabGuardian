#ifndef SEMAPHORE_MANAGER_H
#define SEMAPHORE_MANAGER_H

class SemaphoreManager {
private:
    int semid;

public:
    SemaphoreManager();
    ~SemaphoreManager();

    bool create();
    bool wait();
    bool signal();
};

#endif

