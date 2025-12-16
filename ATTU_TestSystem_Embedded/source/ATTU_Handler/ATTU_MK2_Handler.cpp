#include "ATTU_MK2_Handler.h"

#include <Connection/COM_Configuration.h>
#include <Connection/ConnectionFactory.h>
#include <Connection/IP_Configuration.h>

#include <iostream>

ATTU_MK2_Handler::ATTU_MK2_Handler()
{
    SetUpDataReceiver();
    SetUpDataSender();
}

void ATTU_MK2_Handler::SetUpDataSender()
{
    ConnectionFactory connection_factory;

    COM_Configuration port_config;
    port_config.connection_name = "TestSystem";
    port_config.device          = "/dev/attu20";
    port_config.baudrate        = COM_Configuration::BAUD_9600;

    std::cout << "Opening serial port: " << port_config.device << std::endl;
    auto connection = connection_factory.CreateConnectionPort(port_config);
    connection->Open();

    data_sender = std::make_unique<DataSender>(std::move(connection));
}

void ATTU_MK2_Handler::SetUpDataReceiver()
{
    IP_Configuration config("0.0.0.0",  // listen on all interfaces
                            8060,       // UDP port
                            IP_Configuration::Protocol::UDP, IP_Configuration::Type::SERVER);
    data_receiver = std::make_unique<DataReceiver>(config);
}

ATTU_Response ATTU_MK2_Handler::TagTestData(TestData data_to_tag)
{
    data_sender->SendData(data_to_tag);

    return data_receiver->ReceiveData(data_to_tag.test_data.size());
}

// void ATTU_MK2_Handler::StartHandler()
// {
//     data_receiver->Start_Receiving();
//     data_sender->Start_Sending();
// }
// void ATTU_MK2_Handler::StopHandler()
// {
//     data_sender->Stop_Sending();
//     data_receiver->Stop_Receiving();
// }