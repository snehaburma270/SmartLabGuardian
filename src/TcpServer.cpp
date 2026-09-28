#include "TcpServer.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <fcntl.h>
#include <cerrno>

TcpServer::TcpServer()
    : serverSocket(-1) {
}

TcpServer::~TcpServer() {
    if (serverSocket != -1) {
        close(serverSocket);
    }
}

bool TcpServer::start(int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1) {
        std::cerr << "[-] Failed to create TCP socket.\n";
        return false;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket,
             reinterpret_cast<sockaddr*>(&serverAddress),
             sizeof(serverAddress)) == -1) {

        std::cerr << "[-] Failed to bind TCP socket.\n";
        close(serverSocket);
        serverSocket = -1;
        return false;
    }

    if (listen(serverSocket, 5) == -1) {
        std::cerr << "[-] Failed to listen on TCP socket.\n";
        close(serverSocket);
        serverSocket = -1;
        return false;
    }

    // Make accept() non-blocking.
    int flags = fcntl(serverSocket, F_GETFL, 0);

    if (flags != -1) {
        fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);
    }

    std::cout << "[+] TCP server started on port "
              << port << ".\n";

    return true;
}

bool TcpServer::sendStatus(const std::string& message) {
    if (serverSocket == -1) {
        return false;
    }

    sockaddr_in clientAddress{};
    socklen_t clientSize = sizeof(clientAddress);

    int clientSocket = accept(
        serverSocket,
        reinterpret_cast<sockaddr*>(&clientAddress),
        &clientSize
    );

    // No TCP client connected.
    // Do not block the monitoring system.
    if (clientSocket == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            std::cout << "[i] No TCP client connected. "
                      << "Continuing scan.\n";
        }

        return false;
    }

    ssize_t bytesSent = send(
        clientSocket,
        message.c_str(),
        message.size(),
        0
    );

    close(clientSocket);

    return bytesSent == static_cast<ssize_t>(message.size());
}
