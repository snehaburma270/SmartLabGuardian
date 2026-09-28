#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include <string>

class UdpClient {
private:
    int clientSocket;

public:
    UdpClient();
    ~UdpClient();

    bool sendMessage(const std::string& message,
                     const std::string& ip,
                     int port);
};

#endif
