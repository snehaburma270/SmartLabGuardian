# SmartLab Guardian

## Linux-Based Computer Lab Monitoring & Fault Management System

SmartLab Guardian is a C++ based computer lab monitoring system developed as an individual project for the Wipro Centre of Excellence training.

The system monitors lab computer health, detects common resource problems, generates alerts, and creates maintenance tasks based on priority.

---

## Problem Statement

In a computer laboratory, multiple computers need to be monitored regularly for problems such as:

- High CPU usage
- High RAM usage
- High disk usage
- High temperature
- Network connectivity failure

Manually checking every computer can take time. SmartLab Guardian provides a simple system to monitor these conditions and prioritize maintenance tasks.

---

## Objectives

The main objectives of this project are:

- Monitor computer resource usage
- Check network connectivity
- Detect abnormal resource usage
- Generate alerts for detected problems
- Create prioritized maintenance tasks
- Demonstrate Data Structures and Algorithms
- Apply Linux system monitoring concepts
- Maintain system event logs

---

## Technologies Used

- C++
- Linux / WSL
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
- Priority Queue
- Bubble Sort

### Linux

Linux concepts are used for:

- System resource monitoring
- CPU usage
- RAM usage
- Disk usage
- Network connectivity checking

### Computer Architecture

The project relates to:

- CPU
- Memory
- Storage
- Computer performance
- Hardware and software interaction

### Networking

The project uses basic networking concepts such as:

- IP addresses
- Network connectivity
- Computer nodes
- Ping-based connectivity checking

---

## Main Features

### 1. Computer Registration

The system registers lab computers using:

- Computer ID
- IP address
- Location

Example:

```text
LAB-PC-01
192.168.1.101
Lab-A
```

### 2. Network Connectivity Check

The system checks whether a computer is reachable through the network.

If a computer cannot be reached, it is marked as offline and a critical maintenance task is generated.

### 3. Resource Monitoring

The system monitors:

- CPU usage
- RAM usage
- Disk usage
- Temperature

The local Linux machine provides actual CPU, RAM and disk information.

Other lab computers use simulated values for demonstration.

### 4. Alert Generation

Alerts are generated when resource usage crosses predefined thresholds.

Examples:

```text
CPU usage > 75%
RAM usage > 80%
Disk usage > 90%
Temperature > 82 C
```

Network connection failure is also treated as a critical condition.

### 5. Priority Queue

Maintenance tasks are inserted into a priority queue according to their severity.

Higher-severity tasks are dispatched before lower-severity tasks.

Example:

```text
CRITICAL
HIGH
MEDIUM
LOW
```

### 6. Linear Search

A computer can be searched using its Computer ID.

Example:

```text
LAB-PC-03
```

The system traverses the linked list and searches for the requested computer.

### 7. Bubble Sort

Computers can be sorted according to CPU usage.

The current implementation displays the computers in descending order of CPU usage.

### 8. System Logging

Important events such as computer registration, alerts and dispatched maintenance tasks are written to the system log.

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
└── src/
    ├── Alert.h
    ├── Computer.h
    ├── LabManager.cpp
    ├── LabManager.h
    ├── MaintenanceTask.h
    ├── Monitor.cpp
    ├── Monitor.h
    └── main.cpp
```

---

## How to Compile

Open the Linux/WSL terminal and move to the project directory:

```bash
cd /mnt/c/Users/HP/OneDrive/Desktop/SmartLabGuardian
```

Compile the program using:

```bash
g++ -std=c++17 src/main.cpp src/LabManager.cpp src/Monitor.cpp -o SmartLabGuardian
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
1. Scan & Update Node Health
2. View All Registered Monitored Computers
3. Search Computer by ID (Linear Search)
4. Sort Nodes by CPU Utilization (Bubble Sort)
5. Dispatch Highest Priority Task (Heap Queue)
6. Exit Application
```

---

## Example

After scanning the lab computers, the system may detect:

```text
LAB-PC-02
RAM: 81%
```

and generate a HIGH priority maintenance task.

The priority queue can then dispatch:

```text
Priority: HIGH
Issue: RAM consumption high (>80%)
Status: Dispatched to Lab Sysadmin.
```

---

## DSA Demonstration

The main processing flow is:

```text
Computer Registration
        ↓
Singly Linked List
        ↓
Linear Search
        ↓
Health Monitoring
        ↓
Alert Generation
        ↓
Priority Queue
        ↓
Maintenance Task Dispatch
```

Bubble Sort is also used to arrange computers according to CPU usage.

---

## Limitations

- Only the local Linux machine provides actual system resource values.
- Other lab computers are represented using simulated values for demonstration.
- Temperature values for simulated computers are also simulated.
- The project does not directly control or repair hardware.
- Microcontroller and device-driver concepts are represented at a conceptual/simulation level.

---

## Future Scope

The system can later be extended with:

- Real monitoring agents on multiple lab computers
- A graphical user interface
- Database storage for monitoring history
- More detailed network monitoring
- Hardware sensor integration
- Real device-driver or microcontroller integration

---

## Learning Outcomes

This project helped demonstrate practical use of:

- C++ programming
- Object-Oriented Programming
- Data Structures and Algorithms
- Linux system monitoring
- Operating System concepts
- Computer Architecture
- Networking concepts
- File handling
- Git and GitHub

---

## Author

**Sneha Burma**

B.Tech Computer Science and Engineering  
ITER, SOA University