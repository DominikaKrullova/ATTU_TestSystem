#include "Client.h"

#include <Log.h>

#include <filesystem>
#include <iostream>
#include <oatpp/json/ObjectMapper.hpp>
#include <string>

#include "Broadcast.h"
#include "ClientManager.h"
#include "dto/Packet.h"
#include "dto/TestRequestDTO.h"
#include "service/TestService.h"

oatpp::async::CoroutineStarter Client::onPing(const std::shared_ptr<AsyncWebSocket> &socket,
                                              const oatpp::String                   &message)
{
    INFO("Client ping");
    return socket->sendPongAsync(message);
}

oatpp::async::CoroutineStarter Client::onPong(const std::shared_ptr<AsyncWebSocket> &socket,
                                              const oatpp::String                   &message)
{
    INFO("Client pong");
    return nullptr;
}

oatpp::async::CoroutineStarter Client::onClose(const std::shared_ptr<AsyncWebSocket> &socket, v_uint16 code,
                                               const oatpp::String &message)
{
    INFO("Client closed");
    return nullptr;
}

oatpp::async::CoroutineStarter Client::readMessage(const std::shared_ptr<AsyncWebSocket> &socket, v_uint8 opcode,
                                                   p_char8 data, oatpp::v_io_size size)
{
    if (size < 0)
    {
        ERROR(ReturnCodes::RECEIVE_ERROR, "Negative message size: %lld", size);
        return nullptr;
    }
    else if (size > 0)
    {
        buffer.writeSimple(data, size);
    }
    else
    {
        std::string json = buffer.toString();
        buffer.setCurrentPosition(0);

        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper);
        auto packet = apiObjectMapper->readFromString<oatpp::Object<DTO::Packet>>(json);

        if (packet->packet_type)
        {
            switch (*packet->packet_type)
            {
                case DTO::PacketType::Sync:
                {
                    auto test = apiObjectMapper->readFromString<oatpp::Object<DTO::TestRequestDto>>(json);

                    // Read test_id FROM DTO, not from string
                    std::string test_id = test->payload;  // oatpp::String

                    Broadcast broadcast;

                    // if (test_id)
                    // {
                    std::cout << test_id << std::endl;
                    broadcast.BroadcastTestResult(test_id);
                    // }

                    break;
                }
                default:
                    break;
            }
        }
    }

    return nullptr;
}

void Client::sendMessage(const oatpp::String &message)
{
    class SendMessageCoroutine : public oatpp::async::Coroutine<SendMessageCoroutine>
    {
      private:
        oatpp::async::Lock             *m_lock;
        std::shared_ptr<AsyncWebSocket> m_socket;
        oatpp::String                   m_message;

      public:
        SendMessageCoroutine(oatpp::async::Lock *lock, const std::shared_ptr<AsyncWebSocket> &socket,
                             const oatpp::String &message)
            : m_lock(lock)
            , m_socket(socket)
            , m_message(message)
        {
        }

        Action act() override
        {
            return oatpp::async::synchronize(m_lock, m_socket->sendOneFrameTextAsync(m_message)).next(finish());
        }
    };

    asyncExecutor->execute<SendMessageCoroutine>(&writeLock, this->socket, message);
}