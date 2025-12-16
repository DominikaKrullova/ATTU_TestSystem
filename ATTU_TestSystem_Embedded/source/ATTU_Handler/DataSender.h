#pragma once

// #include <Components/TaskComponent.h>
#include <Connection/Connection.h>
#include <DataTypes/TestData.h>

#include <memory>

class DataSender  //: public TaskComponent
{
  public:
    DataSender(std::unique_ptr<Connection> device_connection);
    ~DataSender();

    // void Start_Sending();
    // void Stop_Sending();

    void SendData(TestData data);

  private:
    // void OnTaskLoop() override;

    std::unique_ptr<Connection> connection;
};
