# SmartLab Guardian

## Linux-Based Computer Lab Monitoring & Fault Management System

SmartLab Guardian is a C++ based computer lab monitoring system designed to monitor the health of computers in a laboratory environment, identify common system problems, generate alerts, and prioritize maintenance tasks.

The project demonstrates concepts learned during the Wipro Centre of Excellence training, including C++, Object-Oriented Programming, Data Structures, Linux, Operating Systems, Computer Architecture, Networking, and Git/GitHub.

---

## Problem Statement

In a computer laboratory, multiple computers need to be monitored regularly.

Problems such as:

- High CPU usage
- High RAM usage
- High disk usage
- High temperature
- Network connectivity failure

can affect the availability and performance of lab computers.

SmartLab Guardian provides a simple way to monitor these conditions and create maintenance tasks when a problem is detected.

---

## Objectives

- Monitor the health of lab computers.
- Check CPU, RAM and disk usage.
- Check network connectivity.
- Detect abnormal system conditions.
- Generate alerts for detected problems.
- Prioritize maintenance tasks.
- Search for a particular computer.
- Sort computers based on CPU usage.
- Maintain a system event log.

---

## Technologies Used

- C++
- Linux / WSL
- Git and GitHub

---

## Concepts Used

### C++ and OOP

The project uses classes and structures to represent:

- Computer
- Monitor
- LabManager
- MaintenanceTask
- Alert

### Data Structures

The following data structures and algorithms are used:

- Singly Linked List
- Priority Queue
- Linear Search
- Bubble Sort

### Linux

Linux system information is obtained using:

- `/proc/stat` for CPU information
- `/proc/meminfo` for memory information
- Linux filesystem information for disk usage
- `ping` for network connectivity checking

### Computer Architecture

The project relates system monitoring to:

- CPU
- RAM
- Storage
- System performance

### Networking

The project uses computer IP addresses and network connectivity checking to determine whether a lab computer is reachable.

---

## Main Features

### 1. Lab Computer Registration

The system maintains a list of registered lab computers containing:

- Computer ID
- IP address
- Location
- CPU usage
- RAM usage
- Disk usage
- Temperature
- Online/Offline status

### 2. System Health Monitoring

The system checks the health of the registered computers.

For the local Linux machine, CPU, RAM and disk information can be obtained from Linux system information.

Other lab nodes are represented as simulated lab machines for demonstration.

### 3. Network Connectivity Check

The system checks whether a registered computer is reachable through its IP address.

If a computer cannot be reached, a critical maintenance task is generated.

### 4. Alert Generation

Alerts are generated when system conditions cross defined thresholds.

Examples include:

- High CPU usage
- High RAM usage
- High disk usage
- High temperature
- Network connection failure

### 5. Priority Queue

Maintenance tasks are inserted into a priority queue.

Tasks with higher severity are dispatched before lower-severity tasks.

Example priority levels:

- CRITICAL
- HIGH
- MEDIUM
- LOW

### 6. Linear Search

A computer can be searched using its Computer ID.

Example:

```text
LAB-PC-03

```markdown
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

---

## How to Compile

Open the Linux/WSL terminal and move to the `src` directory:

```bash
cd src

```markdown
Compile the program using:

```bash
g++ -std=c++17 main.cpp LabManager.cpp Monitor.cpp -o SmartLabGuardian
RUN: ./SmartLabGuardian


Program Menu
============================================
       SMARTLAB GUARDIAN MONITORING
============================================
1. Scan & Update Node Health
2. View All Registered Monitored Computers
3. Search Computer by ID (Linear Search)
4. Sort Nodes by CPU Utilization (Bubble Sort)
5. Dispatch Highest Priority Task (Heap Queue)
6. Exit Application

Example

After scanning the lab computers, the system may detect:

LAB-PC-02
RAM: 81%

and generate a HIGH priority maintenance task.

The priority queue can then dispatch:

Priority: HIGH
Issue: RAM consumption high (>80%)
Status: Dispatched to Lab Sysadmin.
DSA Demonstration

The project demonstrates the following DSA concepts:

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

Bubble Sort is also used to arrange computers according to CPU usage.

Limitations
Only the local Linux machine provides actual system resource values.
Other lab computers are represented using simulated values for demonstration.
Temperature values for simulated computers are also simulated.
The project does not directly control or repair hardware.
Microcontroller and device-driver concepts are represented at a conceptual/simulation level.
Future Scope

The system can later be extended with:

Real monitoring agents on multiple lab computers.
A graphical user interface.
Database storage for monitoring history.
More detailed network monitoring.
Hardware sensor integration.
Real device-driver or microcontroller integration.
Learning Outcomes

This project helped demonstrate practical use of:

C++ programming
Object-Oriented Programming
Data Structures and Algorithms
Linux system monitoring
Operating System concepts
Computer Architecture
Networking concepts
File handling
Git and GitHub
Author

Sneha Burma

B.Tech Computer Science and Engineering
ITER, SOA University
