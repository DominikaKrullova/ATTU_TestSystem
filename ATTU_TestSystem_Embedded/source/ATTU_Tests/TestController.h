#pragma once
#include <ATTU_Handler/ATTU_Handler.h>
#include <ATTU_Tests/VerificationLogic.h>
#include <Generators/TestDataGenerator.h>

#include <memory>

class TestController
{
  public:
    TestController(std::unique_ptr<ATTU_Handler>                 attu_handler_ptr,
                   std::unique_ptr<Generator::TestDataGenerator> data_generator_ptr,
                   std::unique_ptr<VerificationLogic>            verification_logic_ptr);

    bool RunTest();

  private:
    std::unique_ptr<ATTU_Handler>                 attu_handler;
    std::unique_ptr<Generator::TestDataGenerator> data_generator;
    std::unique_ptr<VerificationLogic>            verification_logic;
};
