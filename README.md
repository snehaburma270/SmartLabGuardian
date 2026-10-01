# SmartLab Guardian

## Linux-Based Computer Lab Monitoring & Fault Management System

SmartLab Guardian is a C++-based computer lab monitoring and fault-management system developed as an individual project for the **Wipro Centre of Excellence (Embedded) training**.

The system monitors lab computer health, detects resource-related faults, generates maintenance tasks based on severity, exchanges telemetry using network communication, and demonstrates Linux system-programming and operating-system concepts.

---

## Problem Statement

In a computer laboratory, multiple computers need to be monitored for problems such as:

* High CPU utilization
* High RAM utilization
* High disk utilization
* High temperature
* Network connectivity problems

Manually checking every computer can be time-consuming. SmartLab Guardian provides a command-line monitoring system that detects abnormal conditions and prioritizes maintenance tasks.

---

## Objectives

* Monitor computer resource usage
* Detect abnormal CPU, RAM, disk, and temperature conditions
* Generate maintenance tasks for detected faults
* Prioritize critical maintenance tasks
* Demonstrate Data Structures and Algorithms
* Apply Linux system-programming concepts
* Demonstrate inter-process communication
* Demonstrate TCP and UDP networking
* Maintain synchronized system logs
* Demonstrate C++ Object-Oriented Programming

---

## Technologies Used

* C++17
* Linux
* POSIX system calls
* Linux `/proc` filesystem
* TCP sockets
* UDP sockets
* Shared Memory
* POSIX Semaphore
* File locking
* Git
* GitHub

---

# Concepts Demonstrated

## C++ and Object-Oriented Programming

The project uses:

* Classes
* Structures
* Objects
* Constructors and destructors
* Pointers
* Dynamic memory allocation
* Encapsulation
* File handling
* STL `priority_queue`
* Vectors
* Functions

Major classes include:

* `LabManager`
* `Monitor`
* `TcpServer`
* `UdpClient`
* `SharedMemoryManager`
* `SemaphoreManager`

---

## Data Structures and Algorithms

### Singly Linked List

Lab computers are maintained using a linked list.

Each node contains information such as:

```text
Computer ID
IP Address
Location
CPU Usage
RAM Usage
Disk Usage
Temperature
Online/Offline Status
```

### Linear Search

The system searches for a computer using its ID by traversing the linked list.

Example:

```text
Search: LAB-PC-03
Result: Computer Found
```

### Bubble Sort

Computers can be sorted according to CPU utilization.

The current implementation displays nodes in descending CPU order.

Example:

```text
LAB-PC-03 → 88%
LAB-PC-02 → 78%
LAB-PC-04 → 44%
LAB-PC-01 → 0.1%
```

### Priority Queue / Heap

Maintenance tasks are stored in a C++ `priority_queue`.

Tasks with higher severity are dispatched before lower-severity tasks.

Priority levels:

```text
CRITICAL
HIGH
MEDIUM
LOW
```

---

# Linux and Operating System Concepts

## `/proc` System Monitoring

The project reads Linux system information through the `/proc` filesystem.

The local system provides actual telemetry for:

* CPU
* RAM
* Disk

Other lab nodes use demonstration values.

---

## Shared Memory

Shared memory is used for inter-process communication.

The monitoring process writes node status information into a shared-memory region.

A separate reader program can access the shared telemetry.

This demonstrates fast IPC without repeatedly writing the same information to files.

---

## Semaphore Synchronization

A POSIX semaphore is used to protect shared-memory access.

The basic synchronization flow is:

```text
Wait / Lock
    ↓
Write Shared Memory
    ↓
Signal / Unlock
```

This helps prevent simultaneous access to the shared resource.

---

## File Locking

System events are written to:

```text
data/system_log.txt
```

File locking using `flock()` is used while writing log entries so that concurrent access can be synchronized.

Logged events include:

* Node registration
* Fault detection
* Maintenance-task dispatch

---

# Networking

## TCP

A TCP server is included in the project for status communication.

The server uses a non-blocking `accept()` approach so that the monitoring process can continue even when no TCP client is connected.

Example behavior:

```text
[i] No TCP client connected. Continuing scan.
```

---

## UDP

UDP is used for telemetry transmission.

SmartLab Guardian sends node-status messages to the UDP server.

Example:

```text
Computer: LAB-PC-03 | CPU: 88.000000% | RAM: 90.000000% | Disk: 40.000000%
```

During testing, telemetry from all four configured lab nodes was successfully received by the UDP server.

---

# Computer Architecture

The project connects software monitoring with fundamental computer-system components:

```text
CPU
 │
 ├── CPU Utilization
 │
Memory
 │
 ├── RAM Utilization
 │
Storage
 │
 └── Disk Utilization
```

The monitoring system uses these parameters to identify abnormal computer conditions.

---

# Fault Detection

The system checks predefined thresholds.

| Resource    | Threshold | Severity |
| ----------- | --------: | -------- |
| Disk        |     > 90% | CRITICAL |
| Temperature |    > 82°C | CRITICAL |
| RAM         |     > 80% | HIGH     |
| CPU         |     > 75% | MEDIUM   |

Multiple faults can be generated for the same computer during a single scan.

For example, a computer with both high RAM and high CPU can generate two separate maintenance tasks.

---

# Main Features

## 1. Computer Registration

The system registers four demonstration lab nodes:

```text
LAB-PC-01   192.168.1.101   Lab-A
LAB-PC-02   192.168.1.102   Lab-A
LAB-PC-03   192.168.1.103   Lab-B
LAB-PC-04   192.168.1.104   Lab-B
```

## 2. Health Monitoring

The system scans registered nodes and updates their health information.

## 3. Fault Detection

Resource thresholds are evaluated and maintenance tasks are generated automatically.

## 4. Priority-Based Maintenance

The priority queue ensures that higher-severity tasks are dispatched first.

## 5. Computer Search

A computer can be searched by its ID using Linear Search.

## 6. CPU-Based Sorting

Computers can be sorted using Bubble Sort according to CPU utilization.

## 7. Shared-Memory IPC

Node telemetry can be shared with another process using shared memory.

## 8. Synchronization

Semaphore synchronization protects shared-memory operations.

## 9. Network Telemetry

UDP telemetry and TCP status communication are implemented.

## 10. System Logging

Important events are recorded in `data/system_log.txt` using file locking.

## 11. Linux Device Driver Check

The application checks for the expected character device:

```text
/dev/smartlab
```

The driver source is included in the project.

Because the project was developed and tested in a Linux environment through WSL2, the character device could not be loaded in the development environment. The application therefore reports its availability honestly at runtime.

---

# Program Menu

```text
============================================
       SMARTLAB GUARDIAN MONITORING
============================================
1. Scan & Update Node Health (Telemetry/Proc)
2. View All Registered Monitored Computers
3. Search Computer by ID (Linear Search)
4. Sort Nodes by CPU Utilization (Bubble Sort)
5. Dispatch Highest Priority Task (Heap Queue)
6. Check Linux Device Driver
7. Exit Application
```

---

# Project Structure

```text
SmartLabGuardian/
│
├── .gitignore
├── README.md
│
├── driver/
│   ├── Makefile
│   └── smartlab_driver.c
│
├── data/
│   └── system_log.txt
│
└── src/
    ├── Alert.h
    ├── Computer.h
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
    ├── TcpClient.cpp
    ├── TcpServer.cpp
    ├── TcpServer.h
    ├── UdpClient.cpp
    ├── UdpClient.h
    ├── UdpServer.cpp
    └── main.cpp
```

---

# How to Compile

Open the Linux terminal and move to the project directory:

```bash
cd /mnt/c/Users/HP/OneDrive/Desktop/SmartLabGuardian
```

Compile the main application:

```bash
g++ -std=c++17 \
src/main.cpp \
src/LabManager.cpp \
src/Monitor.cpp \
src/SharedMemoryManager.cpp \
src/SemaphoreManager.cpp \
src/TcpServer.cpp \
src/UdpClient.cpp \
-o SmartLabGuardian
```

Run:

```bash
./SmartLabGuardian
```

---

# Running UDP Telemetry Test

Compile the UDP server:

```bash
g++ src/UdpServer.cpp -o UdpServer
```

Run it:

```bash
./UdpServer
```

Then run SmartLab Guardian and select:

```text
1
```

The UDP server receives telemetry messages from the configured nodes.

---

# Example Fault Detection

During testing, the system detected:

```text
LAB-PC-02
RAM: 81%
CPU: 78%
```

and generated:

```text
HIGH: High memory usage
MEDIUM: CPU threshold breached
```

For another node:

```text
LAB-PC-03
RAM: 90%
CPU: 88%
```

multiple maintenance tasks were generated.

The priority queue dispatched the HIGH-priority task before the MEDIUM-priority task.

---

# System Processing Flow

```text
Computer Registration
        ↓
Singly Linked List
        ↓
System Health Monitoring
        ↓
Fault Detection
        ↓
Alert / Maintenance Task Creation
        ↓
Priority Queue
        ↓
Highest-Priority Task Dispatch
```

Additional processing:

```text
Health Data
    ├──→ Shared Memory
    │        ↓
    │   Semaphore
    │        ↓
    │   IPC Reader
    │
    ├──→ TCP Communication
    │
    └──→ UDP Telemetry
```

---

# Testing Summary

The following components were tested successfully:

| Component                   | Status                |
| --------------------------- | --------------------- |
| C++ application             | Tested                |
| Node registration           | Tested                |
| `/proc` telemetry           | Tested                |
| Linked List                 | Tested                |
| Linear Search               | Tested                |
| Bubble Sort                 | Tested                |
| Priority Queue              | Tested                |
| Multiple fault detection    | Tested                |
| Shared Memory               | Tested                |
| Semaphore synchronization   | Tested                |
| File locking and logging    | Tested                |
| TCP communication           | Tested                |
| UDP communication           | Tested                |
| UDP telemetry from 4 nodes  | Tested                |
| Linux device-driver loading | Not available in the current environment |

---

# Limitations

* The project was developed and tested in a Linux environment through WSL2.
* The Linux character device `/dev/smartlab` could not be loaded in the WSL2 development environment.
* Only the local Linux environment provides actual system telemetry.
* Other lab-node values are simulated for demonstration.
* The configured IP addresses represent demonstration lab nodes.
* The current UDP demonstration uses localhost communication.
* The project does not directly repair or control physical hardware.

---

# Future Scope

The project can be extended with:

* Real monitoring agents installed on multiple lab computers
* Persistent database storage
* Graphical monitoring dashboard
* Real hardware sensor integration
* Real-time alerts
* Advanced network monitoring
* Linux kernel deployment on a compatible environment
* Microcontroller integration
* Remote maintenance management

---

# Learning Outcomes

This project provided practical experience with:

* C++ programming
* Object-Oriented Programming
* Data Structures and Algorithms
* Linux system programming
* `/proc` filesystem
* Inter-Process Communication
* Shared Memory
* Semaphores
* File locking
* TCP/IP networking
* UDP networking
* Computer Architecture
* Operating System concepts
* Linux device-driver concepts
* Git and GitHub

---

## Author

**Sneha Burma**

B.Tech Computer Science and Engineering
ITER, SOA University
