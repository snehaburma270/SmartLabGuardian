#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <string>

class TcpServer {
private:
    int serverSocket;

public:
    TcpServer();
    ~TcpServer();

    bool start(int port);
    bool sendStatus(const std::string& message);
};

#endif
