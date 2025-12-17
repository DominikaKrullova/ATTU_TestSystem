#pragma once

#include <Connection/Connection.h>
#include <DataTypes/TestData.h>

#include <memory>

class DataSender 
{
  public:
    DataSender(std::unique_ptr<Connection> device_connection);
    ~DataSender();

    void SendData(TestData data);

  private:

    std::unique_ptr<Connection> connection;
};
