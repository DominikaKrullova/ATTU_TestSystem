#pragma once

#include <oatpp-websocket/AsyncConnectionHandler.hpp>
#include <unordered_map>

#include "Client.h"

class ClientManager : public oatpp::websocket::AsyncConnectionHandler::SocketInstanceListener
{
  public:
    std::unordered_map<uint32_t, std::shared_ptr<Client>> clients;
    std::mutex                                            mutex;

    void onAfterCreate_NonBlocking(const std::shared_ptr<AsyncWebSocket>     &socket,
                                   const std::shared_ptr<const ParameterMap> &params) override
    {
        auto client = std::make_shared<Client>(socket);
        socket->setListener(client);
        {
            std::lock_guard<std::mutex> guard(mutex);
            ClientManager::clients.insert({client->id, client});
        }
        fprintf(stdout, "Websocket client connection opened. Connection count=%ld\n", clients.size());
    }

    void onBeforeDestroy_NonBlocking(const std::shared_ptr<AsyncWebSocket> &socket) override
    {
        auto client = static_pointer_cast<Client>(socket->getListener());
        {
            std::lock_guard<std::mutex> guard(mutex);
            ClientManager::clients.erase(client->id);
        }
        fprintf(stdout, "Websocket client connection closed. Connection count=%ld\n", clients.size());
    }

    void BroadcastMessage(const oatpp::String &message)
    {
        std::lock_guard<std::mutex> guard(ClientManager::mutex);
        for (auto &[id, client] : ClientManager::clients)
        {
            client->sendMessage(message);
        }
    }
};
