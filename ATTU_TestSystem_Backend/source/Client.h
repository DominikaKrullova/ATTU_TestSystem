#pragma once

#include <oatpp-websocket/AsyncWebSocket.hpp>
#include <oatpp/async/Executor.hpp>
#include <oatpp/async/Lock.hpp>
#include <oatpp/macro/component.hpp>

class Client : public oatpp::websocket::AsyncWebSocket::Listener
{
  public:
    Client(const std::shared_ptr<oatpp::websocket::AsyncWebSocket> &socket)
        : id(next_id++)
        , socket(socket)
    {
    }

    CoroutineStarter onPing(const std::shared_ptr<AsyncWebSocket> &socket, const oatpp::String &message) override;
    CoroutineStarter onPong(const std::shared_ptr<AsyncWebSocket> &socket, const oatpp::String &message) override;
    CoroutineStarter onClose(const std::shared_ptr<AsyncWebSocket> &socket, v_uint16 code,
                             const oatpp::String &message) override;
    CoroutineStarter readMessage(const std::shared_ptr<AsyncWebSocket> &socket, v_uint8 opcode, p_char8 data,
                                 oatpp::v_io_size size) override;

    void sendMessage(const oatpp::String &message);

    const uint32_t                                    id;
    std::shared_ptr<oatpp::websocket::AsyncWebSocket> socket;

    static inline uint32_t next_id = 1;

  private:
    OATPP_COMPONENT(std::shared_ptr<oatpp::async::Executor>, asyncExecutor);
    oatpp::async::Lock                      writeLock;
    oatpp::data::stream::BufferOutputStream buffer;
};
