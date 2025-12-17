#pragma once

#include <Connection/Network/UDP/UDP_ServerSocket.h>
#include <DataTypes/ATTU_Response.h>

#include <memory>
#include <string>
#include <vector>

class DataReceiver  
{
  public:
    explicit DataReceiver(const IP_Configuration& config_ptr);
    ~DataReceiver() = default;

    ATTU_Response ReceiveData(size_t expected_responses);

  private:

    std::unique_ptr<UDP_ServerSocket> udp_server;
    IP_Configuration                  config;
    std::vector<char>                 buffer;
    static constexpr size_t           buffer_size = 200;
};
