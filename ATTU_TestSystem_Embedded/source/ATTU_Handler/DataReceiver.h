#pragma once

// #include <Components/TaskComponent.h>
#include <Connection/Network/UDP/UDP_ServerSocket.h>
#include <DataTypes/ATTU_Response.h>

#include <memory>
#include <string>
#include <vector>

class DataReceiver  //: public TaskComponent
{
  public:
    explicit DataReceiver(const IP_Configuration& config_ptr);
    ~DataReceiver() = default;

    // void Start_Receiving();
    // void Stop_Receiving();

    ATTU_Response ReceiveData(size_t expected_responses);

  private:
    // void OnTaskStartup() override;
    // void OnTaskLoop();

    std::unique_ptr<UDP_ServerSocket> udp_server;
    IP_Configuration                  config;
    std::vector<char>                 buffer;
    static constexpr size_t           buffer_size = 200;
};
