#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main() {

    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (serverSocket == -1) {
        std::cerr << "[-] Failed to create UDP socket.\n";
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(5001);

    if (bind(serverSocket,
             reinterpret_cast<sockaddr*>(&serverAddress),
             sizeof(serverAddress)) == -1) {

        std::cerr << "[-] Failed to bind UDP socket.\n";
        close(serverSocket);
        return 1;
    }

    std::cout << "[+] UDP server started on port 5001.\n";
    std::cout << "[+] Waiting for telemetry messages...\n";

    char buffer[1024];

    // Receive multiple telemetry messages
    for (int i = 0; i < 4; i++) {

        sockaddr_in clientAddress{};
        socklen_t clientSize = sizeof(clientAddress);

        std::memset(buffer, 0, sizeof(buffer));

        int bytesReceived = recvfrom(
            serverSocket,
            buffer,
            sizeof(buffer) - 1,
            0,
            reinterpret_cast<sockaddr*>(&clientAddress),
            &clientSize
        );

        if (bytesReceived > 0) {

            buffer[bytesReceived] = '\0';

            std::cout << "\n========== UDP TELEMETRY ==========\n";
            std::cout << "Message " << (i + 1) << " of 4\n";
            std::cout << "Received: " << buffer << "\n";
        }
    }

    std::cout << "\n[+] Received telemetry from all 4 lab nodes.\n";

    close(serverSocket);

    return 0;
}
