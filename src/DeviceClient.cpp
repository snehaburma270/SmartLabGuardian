#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string devicePath = "/dev/smartlab";

    std::ifstream device(devicePath);

    if (!device.is_open())
    {
        std::cout << "SmartLab device is not available.\n";
        std::cout << "Expected device: " << devicePath << "\n";
        return 1;
    }

    std::string message;

    std::getline(device, message);

    device.close();

    std::cout << "Message from SmartLab Driver:\n";
    std::cout << message << "\n";

    return 0;
}

