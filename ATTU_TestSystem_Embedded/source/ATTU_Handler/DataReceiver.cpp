#include "DataReceiver.h"

#include <Connection/Connection.h>
#include <Connection/Network/NetworkAddress.h>
#include <DataTypes/TaggedData.h>

#include <cctype>   // for std::isprint
#include <cstring>  // for memset
#include <iomanip>  // for timestamps
#include <iostream>
#include <thread>

DataReceiver::DataReceiver(const IP_Configuration& config_ptr)
    : buffer(buffer_size)
{
    config     = config_ptr;
    udp_server = std::make_unique<UDP_ServerSocket>(NetworkAddress(config));
    std::cout << "[UDP] Receiver started on " << config.ip << ":" << config.port << std::endl;
    udp_server->Connect();
}



ATTU_Response DataReceiver::ReceiveData(size_t expected_responses)
{
    ATTU_Response response;

    if (!udp_server)
    {
        std::cerr << "[UDP] Socket not initialized!" << std::endl;
        return response;
    }

    for (size_t i = 0; i < expected_responses; i++)
    {
        std::vector<uint8_t> received(128);

        NetworkSocketInterface::PollResult poll_result = udp_server->Poll(1000);
        if (poll_result == NetworkSocketInterface::PollResult::DATA_TO_READ)
        {
            int bytes_received = udp_server->Receive(received.data(), received.size());

            for (uint8_t i : received)
            {
                std::cout << i << ' ';
            }
            std::cout << std::endl;

            response.test_data.push_back(received);
        }
        else
        {
            response.test_data.push_back(std::vector<uint8_t>());
        }
    }

    return response;
}
