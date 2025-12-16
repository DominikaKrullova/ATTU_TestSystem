#include "TestService.h"

#include <iostream>

std::string runTest(const oatpp::Object<DTO::ATTUConfigDTO> &config)
{
    // if (testName == "PacketLossTest")
    // {
    //     return run_PacketLoss_Test(config);
    // }
    // else if (testName == "DataCorruptionTest")
    // {
    //     return run_DataCorruption_Test(config);
    // }

    return "Unknown test";
}

// std::string TestService::run_PacketLoss_Test(const oatpp::Any& config)
// {
//     std::cout << "[PacketLossTest] Running packet loss test..." << std::endl;

//     return "PacketLossTest executed";
// }

// std::string TestService::run_DataCorruption_Test(const oatpp::Any& config)
// {
//     std::cout << "[DataCorruptionTest] Running data corruption test..." << std::endl;

//     return "DataCorruptionTest executed";
// }
