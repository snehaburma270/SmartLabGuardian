#include "UdpClient.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

UdpClient::UdpClient()
    : clientSocket(-1) {
}

UdpClient::~UdpClient() {
    if (clientSocket != -1) {
        close(clientSocket);
    }
}

bool UdpClient::sendMessage(const std::string& message,
                            const std::string& ip,
                            int port) {

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (clientSocket == -1) {
        std::cerr << "[-] Failed to create UDP socket.\n";
        return false;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(),
                  &serverAddress.sin_addr) <= 0) {
        std::cerr << "[-] Invalid UDP destination IP.\n";
        close(clientSocket);
        clientSocket = -1;
        return false;
    }

    int bytesSent = sendto(
        clientSocket,
        message.c_str(),
        message.size(),
        0,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress)
    );

    if (bytesSent == -1) {
        std::cerr << "[-] Failed to send UDP message.\n";
        close(clientSocket);
        clientSocket = -1;
        return false;
    }

    std::cout << "[+] UDP telemetry sent successfully.\n";

    close(clientSocket);
    clientSocket = -1;

    return true;
}
