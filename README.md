# SmartLab Guardian

## Linux-Based Computer Lab Monitoring & Fault Management System

SmartLab Guardian is a C++-based computer lab monitoring and resource management system developed as an individual project for the Wipro Centre of Excellence training.

The system monitors lab computer health, detects resource-related faults, generates maintenance tasks according to priority, and manages computer availability for users.

---

## Problem Statement

In a computer laboratory, multiple computers need to be monitored regularly for problems such as:

* High CPU usage
* High RAM usage
* High disk usage
* High temperature
* Network connectivity failure

Manually checking every computer can take time. SmartLab Guardian provides a system to monitor these conditions, detect faults, prioritize maintenance tasks, and manage available computers.

---

## Objectives

The main objectives of this project are:

* Monitor computer resource usage
* Check network connectivity
* Detect abnormal resource usage
* Generate alerts for detected problems
* Create prioritized maintenance tasks
* Manage computer availability
* Request a suitable computer based on RAM and CPU requirements
* Release an assigned computer
* Prevent faulty computers from being assigned
* Demonstrate Data Structures and Algorithms
* Apply Linux system programming and monitoring concepts
* Demonstrate networking concepts
* Maintain system event logs

---

## Technologies Used

* C++
* C
* Linux / WSL2
* Git
* GitHub

---

## Concepts Demonstrated

### C++ and OOP

The project uses:

* Classes
* Structures
* Objects
* Functions
* Pointers
* Dynamic memory allocation
* File handling

### Data Structures and Algorithms

The project demonstrates:

* Singly Linked List
* Linear Search
* Priority Queue
* Bubble Sort

### Linux System Programming

Linux concepts demonstrated include:

* `/proc` system monitoring
* CPU usage monitoring
* RAM usage monitoring
* Disk usage monitoring
* File handling
* Shared memory
* Semaphore synchronization
* File locking
* System logging
* Linux device-driver concepts

### Computer Architecture

The project relates to:

* CPU
* Memory
* Storage
* Computer performance
* Hardware and software interaction

### Networking

The project demonstrates:

* IP addresses
* Computer nodes
* TCP communication
* UDP communication
* Network connectivity
* Telemetry transmission

---

## Main Features

### 1. Computer Registration

The system registers lab computers using:

* Computer ID
* IP address
* Location

Example:

```text
LAB-PC-01
192.168.1.101
Lab-A
```

Four demonstration lab computers are registered:

```text
LAB-PC-01 → 192.168.1.101 → Lab-A
LAB-PC-02 → 192.168.1.102 → Lab-A
LAB-PC-03 → 192.168.1.103 → Lab-B
LAB-PC-04 → 192.168.1.104 → Lab-B
```

---

### 2. Network Connectivity Check

The system checks the connectivity status of monitored computers.

If a computer is detected as offline, it can be marked unavailable and a critical maintenance task can be generated.

---

### 3. Resource Monitoring

The system monitors:

* CPU usage
* RAM usage
* Disk usage
* Temperature

The local Linux machine provides actual CPU, RAM, and disk information.

Other lab computers use simulated values for demonstration.

---

### 4. Fault Detection

Alerts and maintenance tasks are generated when predefined thresholds are crossed.

Current thresholds include:

```text
CPU usage > 75%
RAM usage > 80%
Disk usage > 90%
Temperature > 82 C
```

Network connectivity failure is also treated as a critical condition.

When a fault is detected, the affected computer is marked:

```text
FAULTY
```

Faulty computers are not available for new computer requests.

---

### 5. Maintenance Priority Queue

Maintenance tasks are stored in a priority queue according to severity.

Higher-severity tasks are dispatched before lower-severity tasks.

Priority levels include:

```text
CRITICAL
HIGH
MEDIUM
LOW
```

Example:

```text
Task ID    : 1
Target Node: LAB-PC-02
Priority   : [HIGH]
Issue      : RAM consumption high (>80%)
```

---

### 6. Computer Resource Management

SmartLab Guardian can assign a suitable computer according to user requirements.

The user provides:

* Minimum required RAM
* Maximum acceptable CPU usage

The system checks:

```text
Computer is AVAILABLE
        AND
Computer is ONLINE
        AND
Available RAM >= required RAM
        AND
CPU usage <= maximum CPU
```

Available RAM is calculated as:

```text
Available RAM = 100% - Current RAM Usage
```

If all conditions are satisfied, the computer is marked:

```text
ASSIGNED
```

---

### 7. Computer Release

An assigned computer can be released after use.

The availability changes:

```text
ASSIGNED → AVAILABLE
```

A computer marked as `FAULTY` cannot be released as an available computer.

---

### 8. Computer Availability States

Each computer can have one of the following availability states:

```text
AVAILABLE
ASSIGNED
FAULTY
```

Example from testing:

```text
LAB-PC-01 → ASSIGNED
LAB-PC-02 → FAULTY
LAB-PC-03 → FAULTY
LAB-PC-04 → AVAILABLE
```

This allows the system to distinguish between computers that are ready for use, currently assigned, and unavailable because of faults.

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
LAB-PC-03 → 88.0%
LAB-PC-02 → 78.0%
LAB-PC-04 → 44.0%
LAB-PC-01 → 0.1%
```

---

### 11. TCP Communication

The project includes TCP communication for communication between the monitoring system and lab-node services.

The TCP server runs on:

```text
Port: 5000
```

If no TCP client is connected during a scan, the application continues without blocking the monitoring process.

---

### 12. UDP Telemetry

The project uses UDP for telemetry transmission.

During testing, UDP telemetry was successfully sent through the local demonstration environment.

---

### 13. Shared Memory and Semaphore

The project demonstrates inter-process communication using:

* Shared memory
* Semaphore synchronization

Shared memory is used for exchanging information between processes, while the semaphore provides synchronization.

---

### 14. System Logging

Important events are written to:

```text
data/system_log.txt
```

The log can contain events such as:

* Computer registration
* Fault detection
* Alerts
* Maintenance tasks
* Computer availability changes
* Task dispatch

---

### 15. Linux Device Driver Check

The project includes a Linux character-device driver source:

```text
driver/smartlab_driver.c
```

The application checks whether the expected device exists:

```text
/dev/smartlab
```

In the current WSL2 development environment, `/dev/smartlab` is not available.

Therefore, the application reports the device status honestly instead of claiming that the driver has been loaded.

The driver can be loaded and tested on a compatible Linux kernel environment.

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

Open a Linux/WSL2 terminal and move to the project directory:

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

## System Workflow

The main monitoring workflow is:

```text
Lab Computer Registration
          ↓
System Resource Monitoring
          ↓
Network Connectivity Check
          ↓
Fault Detection
          ↓
┌─────────────────────┐
│ Fault Detected?     │
└──────────┬──────────┘
           │
      Yes  ↓
     Mark FAULTY
           ↓
 Create Maintenance Task
           ↓
   Priority Queue
           ↓
 Dispatch Task
```

Computer resource management works as:

```text
User Requests Computer
          ↓
Check AVAILABLE State
          ↓
Check ONLINE Status
          ↓
Check Available RAM
          ↓
Check Maximum CPU
          ↓
      Suitable?
       /      \
     Yes       No
      ↓         ↓
  ASSIGNED   Try Next Node
      ↓
  User Uses PC
      ↓
   Release
      ↓
  AVAILABLE
```

---

## Example Testing Results

During testing, the system detected:

```text
LAB-PC-02
RAM: 81%
```

and:

```text
LAB-PC-03
CPU: 88%
RAM: 90%
```

These computers were marked:

```text
FAULTY
```

A suitable computer request successfully assigned:

```text
LAB-PC-01
```

The system also successfully released the computer:

```text
ASSIGNED → AVAILABLE
```

The tested system state was:

```text
LAB-PC-01 → AVAILABLE / ASSIGNED during testing
LAB-PC-02 → FAULTY
LAB-PC-03 → FAULTY
LAB-PC-04 → AVAILABLE
```

The priority queue successfully dispatched a HIGH-priority task for `LAB-PC-02`.

Bubble Sort successfully arranged the computers by descending CPU usage.

Linear Search successfully found `LAB-PC-03` and displayed its current status and availability.

---

## Limitations

* The project was developed and tested using a Linux environment through WSL2.
* Only the local Linux machine provides actual system resource telemetry.
* Other lab computers are represented using simulated values for demonstration.
* Temperature values for simulated computers are also simulated.
* The network addresses used for demonstration do not represent a real multi-computer laboratory deployment.
* UDP communication was tested in the local demonstration environment.
* The `/dev/smartlab` character device is not available in the current WSL2 environment.
* The Linux character driver was therefore not loaded as a kernel module during WSL2 testing.
* The project does not directly control or physically repair hardware.
* The current implementation does not provide a graphical user interface.

---

## Future Scope

The system can later be extended with:

* Real monitoring agents on multiple lab computers
* Native Linux deployment
* A graphical user interface
* Database storage for monitoring history
* More detailed network monitoring
* Hardware sensor integration
* Real device-driver integration
* Microcontroller-based monitoring
* Remote maintenance management

---

## Learning Outcomes

This project helped demonstrate practical use of:

* C++ programming
* Object-Oriented Programming
* Data Structures and Algorithms
* Linux system programming
* Linux system monitoring
* Operating System concepts
* Computer Architecture
* Networking concepts
* TCP and UDP communication
* Inter-process communication
* Shared memory
* Semaphore synchronization
* File handling
* Linux device-driver concepts
* Git and GitHub

---

## Project Information

**Sneha Burma**

B.Tech Computer Science and Engineering
ITER, SOA University
