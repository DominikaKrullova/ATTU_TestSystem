#include "Broadcast.h"

#include <ATTU_Handler/ATTU_Handler.h>
#include <ATTU_Handler/ATTU_MK2_Handler.h>
#include <ATTU_Tests/ASCII_Protocol_Test.h>
#include <ATTU_Tests/VerificationLogic.h>
#include <Generators/ASCII_Generator.h>

#include <memory>

#include "OatppComponents.h"
#include "dto/Packet.h"

Broadcast::Broadcast()
{
    std::unique_ptr<Generator::TestDataGenerator> generator;
    std::unique_ptr<ATTU_Handler>                 attu_handler;
    std::unique_ptr<VerificationLogic>            verification;

    try
    {
        generator    = std::make_unique<Generator::ASCII_Generator>();
        attu_handler = std::make_unique<ATTU_MK2_Handler>();
        verification = std::make_unique<ASCII_Protocol_Test>();
        test_controller =
            std::make_unique<TestController>(std::move(attu_handler), std::move(generator), std::move(verification));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Broadcast::BroadcastTestResult(std::string test_id)
{
    bool result = test_controller->RunTest();

    auto dto = DTO::TestResult::createShared();
    // dto->packet_type = DTO::PacketType::TestResult;
    dto->test_id = test_id;
    // dto->status      = result;
    dto->result = result;

    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper);
    auto message = apiObjectMapper->writeToString(dto);

    OATPP_COMPONENT(std::shared_ptr<ClientManager>, clientManager);
    clientManager->BroadcastMessage(message);
}
