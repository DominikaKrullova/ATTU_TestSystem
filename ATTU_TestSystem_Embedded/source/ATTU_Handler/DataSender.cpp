#include "DataSender.h"

#include <Log.h>

DataSender::DataSender(std::unique_ptr<Connection> device_connection)
// : TaskComponent("DataSender")
{
    connection = std::move(device_connection);

    if (!connection)
    {
        throw std::invalid_argument("Communication ptr in NULL.");
    }

    if (!connection->Open())
    {
        ERROR(ReturnCodes::SOCKET_CONNECT_FAIL, "Unable to open connection to device");
        throw std::exception();
    }
}

DataSender::~DataSender()
{
    connection = nullptr;
}

void DataSender::SendData(TestData data)
{
    for (auto &&i : data.test_data)
    {
        connection->Write(i.data(), i.size());
        std::cout << i.data() << " ";
    }
}

// void DataSender::Start_Sending()
// {
//     StartTask();
// }
// void DataSender::Stop_Sending()
// {
//     StopTaskAndJoin();
// }

// void DataSender::OnTaskLoop()
// {
//     while (IsRunning())
//     {
//         SendData();
//         std::this_thread::sleep_for(std::chrono::seconds(1));
//     }
// }