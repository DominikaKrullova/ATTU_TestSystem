#include "TestController.h"

TestController::TestController(std::unique_ptr<ATTU_Handler>                 attu_handler_ptr,
                               std::unique_ptr<Generator::TestDataGenerator> data_generator_ptr,
                               std::unique_ptr<VerificationLogic>            verification_logic_ptr)
{
    attu_handler       = std::move(attu_handler_ptr);
    data_generator     = std::move(data_generator_ptr);
    verification_logic = std::move(verification_logic_ptr);
}

bool TestController::RunTest()
{
    auto test_data = data_generator->GenerateTestData();

    auto tagged_data = attu_handler->TagTestData(test_data);
    for (int i = 0; i < tagged_data.test_data.size(); i++)
    {
        std::string tagged_data_str(tagged_data.test_data[i].begin(), tagged_data.test_data[i].end());
        std::string data_str(test_data.test_data[i].begin(), test_data.test_data[i].end());

        printf("Tagged data: %s - ", tagged_data_str.c_str());
        printf("Test data: %s\n", data_str.c_str());
    }

    return verification_logic->Verify(test_data, tagged_data);
}