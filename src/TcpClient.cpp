#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket == -1) {
        std::cout << "[-] Failed to create TCP client socket.\n";
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(5000);

    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    if (connect(clientSocket,
                reinterpret_cast<sockaddr*>(&serverAddress),
                sizeof(serverAddress)) == -1) {
        std::cout << "[-] Failed to connect to TCP server.\n";
        close(clientSocket);
        return 1;
    }

    char buffer[1024] = {0};

    int bytesRead = recv(clientSocket,
                         buffer,
                         sizeof(buffer) - 1,
                         0);

    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';

        std::cout << "\n========== TCP CLIENT ==========\n";
        std::cout << "Received: " << buffer << "\n";
    }

    close(clientSocket);

    return 0;
}

