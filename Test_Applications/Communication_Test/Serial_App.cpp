#include <Connection/COM_Configuration.h>
#include <Connection/ConnectionFactory.h>
#include <Connection/Network/UDP/UDP_ServerSocket.h>
#include <Connection/Serial/COM_Connection.h>
#include <DataReceiver.h>
#include <DataSender.h>

#include <iomanip>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

std::shared_ptr<DataSender>   data_sender;
std::shared_ptr<DataReceiver> data_receiver;

int main(int argc, char* argv[])
{
    ConnectionFactory connection_factory;

    // --- SERIAL CONFIGURATION (for DataSender) ---
    COM_Configuration port_config;
    port_config.connection_name = "TestSystem";
    port_config.device          = "/dev/attu20";
    port_config.baudrate        = COM_Configuration::BAUD_9600;

    std::cout << "Opening serial port: " << port_config.device << std::endl;
    auto connection = connection_factory.CreateConnectionPort(port_config);
    connection->Open();

    // --- NETWORK CONFIGURATION (for DataReceiver) ---
    IP_Configuration config("0.0.0.0",  // listen on all interfaces
                            8060,       // UDP port
                            IP_Configuration::Protocol::UDP, IP_Configuration::Type::SERVER);

    data_sender   = std::make_shared<DataSender>(std::move(connection));
    data_receiver = std::make_shared<DataReceiver>(config);

    std::cout << "System started — sending over serial, receiving over UDP..." << std::endl;

    data_sender->Start_Sending();
    data_receiver->Start_Receiving();

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        // Optionally print statistics here
    }

    data_sender->Stop_Sending();
    data_receiver->Stop_Receiving();

    return 0;
}
