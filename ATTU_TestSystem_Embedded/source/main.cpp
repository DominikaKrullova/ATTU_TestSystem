#include <ATTU_Handler/ATTU_Handler.h>
#include <ATTU_Handler/ATTU_MK2_Handler.h>
#include <ATTU_Tests/ASCII_Protocol_Test.h>
#include <ATTU_Tests/TestController.h>
#include <ATTU_Tests/VerificationLogic.h>
#include <Generators/ASCII_Generator.h>

#include <iostream>
#include <memory>
#include <thread>

int main(int argc, char* argv[])
{
    std::unique_ptr<Generator::TestDataGenerator> generator;
    std::unique_ptr<ATTU_Handler>                 attu_handler;
    std::unique_ptr<VerificationLogic>            verification;
    std::unique_ptr<TestController>               test_controller;

    try
    {
        generator    = std::make_unique<Generator::ASCII_Generator>();
        attu_handler = std::make_unique<ATTU_MK2_Handler>();
        verification = std::make_unique<ASCII_Protocol_Test>();
        test_controller =
            std::make_unique<TestController>(std::move(attu_handler), std::move(generator), std::move(verification));
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (size_t i = 0; i < 5; i++)
    {
        if (test_controller->RunTest())
        {
            printf("Test passed!\n");
        }
        // else
        // {
        //     // printf("Test failed");
        // }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}
