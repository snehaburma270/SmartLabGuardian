#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>


struct Computer {
    std::string id;          
    std::string ipAddress;   
    std::string location;    
    double cpuUsage;         
    double ramUsage;         
    double diskUsage;        
    int temperature;         
    bool isOnline;

    Computer* next;          

    
    Computer(std::string id_, std::string ip_, std::string loc_)
        : id(id_), ipAddress(ip_), location(loc_),
          cpuUsage(0.0), ramUsage(0.0), diskUsage(0.0),
          temperature(42), isOnline(true), next(nullptr) {}
};

#endif
