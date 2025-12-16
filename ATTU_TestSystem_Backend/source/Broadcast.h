#pragma once

#include <ATTU_Tests/TestController.h>

#include <iostream>
#include <oatpp/json/ObjectMapper.hpp>

class Broadcast
{
  public:
    Broadcast();
    virtual ~Broadcast() = default;

    void BroadcastTestResult(std::string test_id);

  private:
    std::unique_ptr<TestController> test_controller;
};
