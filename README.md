# SmartLab Guardian

## Linux-Based Computer Lab Monitoring & Fault Management System

SmartLab Guardian is a C++ based computer lab monitoring and resource management system developed as an individual project for the Wipro Centre of Excellence training.

The system monitors lab computer health, detects resource-related problems, generates alerts, creates prioritized maintenance tasks, and manages computer availability.

---

## Problem Statement

In a computer laboratory, multiple computers need to be monitored regularly for problems such as:

- High CPU usage
- High RAM usage
- High disk usage
- High temperature
- Network connectivity failure
- Computer availability and assignment status

Manually checking every computer can take time. SmartLab Guardian provides a centralized command-line system to monitor computer health, detect faults, prioritize maintenance, and manage available lab computers.

---

## Objectives

The main objectives of this project are:

- Monitor computer resource usage
- Check network connectivity
- Detect abnormal resource usage
- Generate alerts for detected problems
- Create prioritized maintenance tasks
- Manage computer resource requests and releases
- Track computer availability states
- Demonstrate Data Structures and Algorithms
- Apply Linux system programming concepts
- Demonstrate networking and inter-process communication
- Maintain system event logs
- Demonstrate Linux device-driver concepts

---

## Technologies Used

- C++
- C
- Linux / WSL2
- Git
- GitHub

---

## Concepts Demonstrated

### C++ and OOP

The project uses:

- Classes
- Structures
- Objects
- Functions
- Pointers
- Dynamic memory allocation
- File handling

### Data Structures and Algorithms

The project demonstrates:

- Singly Linked List
- Linear Search
- Priority Queue / Heap
- Bubble Sort

### Linux System Programming

Linux concepts are used for:

- `/proc` system monitoring
- CPU usage monitoring
- RAM usage monitoring
- Disk usage monitoring
- File locking
- System logging
- Shared memory
- Semaphore synchronization
- Device-driver interface checking

### Computer Architecture

The project relates to:

- CPU
- Memory
- Storage
- Computer performance
- Hardware and software interaction

### Networking

The project demonstrates:

- IP addresses
- Network connectivity
- TCP communication
- UDP communication
- Computer nodes
- Telemetry transmission

---

## Software Architecture

SmartLab Guardian follows a modular software architecture in which the main C++ application coordinates monitoring, resource management, fault management, data structures, networking, Linux system programming, and device-driver components.

```text
                    ┌─────────────────────────┐
                    │    User / Lab Admin     │
                    └────────────┬────────────┘
                                 │
                                 ▼
                    ┌─────────────────────────┐
                    │    CLI Interface        │
                    │       main.cpp          │
                    └────────────┬────────────┘
                                 │
                                 ▼
                    ┌─────────────────────────┐
                    │       LabManager        │
                    │    Central Controller   │
                    └────────────┬────────────┘
                                 │
          ┌──────────────────────┼──────────────────────┐
          │                      │                      │
          ▼                      ▼                      ▼
 ┌─────────────────┐   ┌─────────────────┐   ┌─────────────────┐
 │   Monitoring    │   │    Resource     │   │ Fault Management│
 │     Module      │   │   Management    │   │                 │
 └────────┬────────┘   └────────┬────────┘   └────────┬────────┘
          │                     │                     │
          ▼                     ▼                     ▼
     Linux /proc         Computer Objects       Threshold Check
   CPU/RAM/Disk/Temp          │                     │
                              ▼                     ▼
                     Linked List / Search      Priority Queue
                              │                     │
                              ▼                     ▼
                         Bubble Sort          Maintenance Tasks

          ┌──────────────────────┬──────────────────────┐
          │                      │                      │
          ▼                      ▼                      ▼
 ┌─────────────────┐   ┌─────────────────┐   ┌─────────────────┐
 │   Networking    │   │       IPC       │   │ System Logging  │
 │    TCP / UDP    │   │ Shared Memory   │   │                 │
 └─────────────────┘   │   + Semaphore   │   └─────────────────┘
                       └─────────────────┘

                              │
                              ▼
                    ┌─────────────────────────┐
                    │ Linux Device Driver     │
                    │    /dev/smartlab        │
                    └─────────────────────────┘
```

---

## Architecture Flow

1. The user interacts with the command-line interface through `main.cpp`.
2. `LabManager` acts as the central controller.
3. The monitoring module collects system information using Linux `/proc`.
4. Resource management handles computer requests and releases.
5. Fault management evaluates resource thresholds.
6. Faulty computers are marked as `FAULTY`.
7. Maintenance problems are inserted into a priority queue according to severity.
8. Computer objects are maintained using a singly linked list.
9. Linear Search is used to find computers by ID.
10. Bubble Sort is used to arrange computers according to CPU usage.
11. TCP and UDP modules demonstrate network communication.
12. Shared memory and semaphores demonstrate inter-process communication and synchronization.
13. Important events are stored in `data/system_log.txt`.
14. The Linux device-driver interface checks whether `/dev/smartlab` is available.

---

## Main Features

### 1. Computer Registration

The system maintains registered lab computers using:

- Computer ID
- IP address
- Location
- CPU usage
- RAM usage
- Disk usage
- Temperature
- Online status
- Availability state

Example:

```text
LAB-PC-01
192.168.1.101
Lab-A
```

---

### 2. Network Connectivity Check

The system checks whether a computer is reachable through the network.

If a computer cannot be reached, it can be treated as an offline condition and a critical maintenance task can be generated.

---

### 3. Resource Monitoring

The system monitors:

- CPU usage
- RAM usage
- Disk usage
- Temperature

The local Linux machine provides actual CPU, RAM and disk information through Linux system interfaces.

Other lab computer values are simulated for demonstration.

---

### 4. Fault Detection

The system evaluates predefined resource thresholds.

Examples:

```text
CPU usage > 75%
RAM usage > 80%
Disk usage > 90%
Temperature > 82 C
```

When a threshold is exceeded, the corresponding computer can be marked as `FAULTY` and a maintenance task is generated.

---

### 5. Maintenance Priority Queue

Maintenance tasks are stored using a priority queue.

Tasks are prioritized according to severity:

```text
CRITICAL
HIGH
MEDIUM
LOW
```

Higher-priority maintenance tasks are dispatched before lower-priority tasks.

Example:

```text
Task ID    : 1
Target Node: LAB-PC-02
Priority   : [HIGH]
Issue      : RAM consumption high (>80%)
```

---

### 6. Computer Resource Management

The system allows a user to request an available computer based on:

- Minimum required available RAM
- Maximum acceptable CPU usage
- Computer availability
- Online status

Available RAM is calculated from the monitored RAM usage.

A computer is assigned only when it satisfies the requested conditions.

Faulty computers are not assigned.

---

### 7. Computer Release

An assigned computer can be released using its Computer ID.

The availability state changes:

```text
ASSIGNED → AVAILABLE
```

A computer marked as `FAULTY` is not returned to the available pool until its fault condition is resolved.

---

### 8. Computer Availability States

Each computer can have one of the following states:

```text
AVAILABLE
ASSIGNED
FAULTY
```

This allows the system to distinguish between:

- Computers available for use
- Computers currently assigned
- Computers requiring maintenance

---

### 9. Linear Search

A computer can be searched using its Computer ID.

Example:

```text
LAB-PC-03
```

The system traverses the linked list and searches for the requested computer.

---

### 10. Bubble Sort

Computers can be sorted according to CPU usage.

The current implementation displays computers in descending order of CPU utilization.

Example:

```text
LAB-PC-03 | CPU: 88.0%
LAB-PC-02 | CPU: 78.0%
LAB-PC-04 | CPU: 44.0%
LAB-PC-01 | CPU: 0.1%
```

---

### 11. TCP Communication

The project includes a TCP server module for demonstrating reliable network communication between the application and a client.

The TCP server uses port `5000`.

During the WSL2 demonstration, the application continues safely when no TCP client is connected.

---

### 12. UDP Telemetry

The project includes UDP communication for telemetry transmission.

The current demonstration uses localhost UDP communication for testing.

---

### 13. Shared Memory and Semaphore

The project demonstrates Linux inter-process communication using:

- Shared Memory
- Semaphore synchronization

Shared memory allows processes to access a common memory region, while the semaphore helps coordinate access.

---

### 14. System Logging

Important system events are recorded in:

```text
data/system_log.txt
```

Examples include:

- Fault detection
- Maintenance events
- System events
- Resource management events

---

### 15. Linux Device Driver Interface

The project includes a Linux character-device driver source:

```text
driver/smartlab_driver.c
```

The application checks for the expected device:

```text
/dev/smartlab
```

The driver could not be compiled and loaded in the current WSL2 environment because the required compatible kernel build environment was unavailable.

Therefore, the project does **not** claim that the driver is currently loaded.

---

## Project Structure

```text
SmartLabGuardian/
│
├── .gitignore
├── README.md
│
├── data/
│   └── system_log.txt
│
├── driver/
│   ├── Makefile
│   └── smartlab_driver.c
│
└── src/
    ├── Alert.h
    ├── Computer.h
    ├── DeviceClient
    ├── DeviceClient.cpp
    ├── LabManager.cpp
    ├── LabManager.h
    ├── MaintenanceTask.h
    ├── Monitor.cpp
    ├── Monitor.h
    ├── SemaphoreManager.cpp
    ├── SemaphoreManager.h
    ├── SharedMemoryManager.cpp
    ├── SharedMemoryManager.h
    ├── SharedMemoryReader.cpp
    ├── SmartLabGuardian
    ├── TcpClient.cpp
    ├── TcpServer.cpp
    ├── TcpServer.h
    ├── UdpClient.cpp
    ├── UdpClient.h
    ├── UdpServer.cpp
    └── main.cpp
```

---

## How to Compile

Open the Linux/WSL terminal and move to the project directory:

```bash
cd /mnt/c/Users/HP/OneDrive/Desktop/SmartLabGuardian
```

Compile the main application using:

```bash
g++ -std=c++17 src/main.cpp src/LabManager.cpp src/Monitor.cpp src/SemaphoreManager.cpp src/SharedMemoryManager.cpp src/TcpServer.cpp src/UdpClient.cpp -o SmartLabGuardian
```

Run the program:

```bash
./SmartLabGuardian
```

---

## Program Menu

```text
============================================
       SMARTLAB GUARDIAN MONITORING
============================================
1. Scan & Update Node Health (Telemetry/Proc)
2. Request a Computer
3. Release a Computer
4. View All Registered Monitored Computers
5. Search Computer by ID (Linear Search)
6. Sort Nodes by CPU Utilization (Bubble Sort)
7. Dispatch Highest Priority Task (Heap Queue)
8. Check Linux Device Driver
9. Exit Application
```

---

## Example Workflow

The main system workflow is:

```text
Start Application
       ↓
Initialize Shared Memory
       ↓
Initialize Semaphore
       ↓
Start TCP Server
       ↓
Scan Computer Nodes
       ↓
Collect Linux Telemetry
       ↓
Evaluate Fault Conditions
       ↓
Mark Faulty Computers
       ↓
Create Maintenance Tasks
       ↓
Update Priority Queue
       ↓
Request / Release Computer
       ↓
Search / Sort Computers
       ↓
Dispatch Maintenance Task
       ↓
Check Device Driver
       ↓
Save System Logs
       ↓
Exit
```

---

## DSA Demonstration

The project demonstrates multiple Data Structures and Algorithms:

```text
Computer Objects
       ↓
Singly Linked List
       ↓
Linear Search
       ↓
Bubble Sort
       ↓
Priority Queue / Heap
       ↓
Maintenance Task Dispatch
```

### Singly Linked List

Computer objects are maintained using a singly linked list.

### Linear Search

The linked list is traversed to locate a computer using its ID.

### Bubble Sort

The computers are arranged according to CPU utilization.

### Priority Queue

Maintenance tasks are organized according to their priority so that higher-severity problems can be dispatched first.

---

## Testing Results

The following functionality was tested successfully in the WSL2 environment:

- Linux system monitoring
- Computer fault detection
- Faulty computer identification
- Computer resource request
- Computer release
- Availability state management
- Linear search
- Bubble sort
- Priority queue maintenance task dispatch
- TCP server initialization
- UDP telemetry transmission
- Shared memory initialization
- Semaphore initialization
- System logging
- Linux device-driver availability check

Example resource-management result:

```text
[+] Computer Assigned Successfully

Computer: LAB-PC-01
IP Address: 192.168.1.101
Location: Lab-A
Available RAM: 93.8052%
Current CPU Usage: 0.117218%
```

Example fault detection:

```text
[!] LAB-PC-02 marked as FAULTY.
[!] LAB-PC-03 marked as FAULTY.
```

Example maintenance task:

```text
Task ID    : 1
Target Node: LAB-PC-02
Priority   : [HIGH]
Issue      : RAM consumption high (>80%)
```

---

## Execution Environment and Limitations

- The project was developed and tested in a Linux environment provided through WSL2 on Windows.
- Only the local Linux environment provides actual CPU, RAM and disk telemetry.
- Other lab computer values are simulated for demonstration.
- The project does not directly repair or control physical hardware.
- UDP communication is demonstrated using localhost in the current test environment.
- The Linux character-driver source is included, but the driver could not be compiled and loaded in the current WSL2 environment because a compatible kernel build environment was unavailable.
- `/dev/smartlab` is therefore unavailable during the current demonstration.
- A compatible native Linux kernel environment can be used for actual driver compilation and loading.

---

## Future Scope

The system can later be extended with:

- Real monitoring agents on multiple lab computers
- A graphical user interface
- Database storage for monitoring history
- Real-time monitoring dashboards
- More detailed network monitoring
- Hardware sensor integration
- Native Linux device-driver integration
- Remote maintenance management
- Authentication and role-based access

---

## Learning Outcomes

This project helped demonstrate practical use of:

- C++ programming
- Object-Oriented Programming
- Data Structures and Algorithms
- Linux system programming
- Operating System concepts
- Computer Architecture
- Networking concepts
- Inter-Process Communication
- File handling
- Git and GitHub
- Linux device-driver concepts

---

