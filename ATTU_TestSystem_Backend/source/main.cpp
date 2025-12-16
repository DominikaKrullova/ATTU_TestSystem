#include <csignal>
#include <filesystem>
#include <iostream>
#include <oatpp/network/Server.hpp>
#include <oatpp/web/server/HttpRequestHandler.hpp>

#include "OatppComponents.h"
#include "service/WebSocketService.h"

uint16_t OatppComponents::PORT;

volatile std::sig_atomic_t keepRunning = 1;
void                       handle_signal(int signal)
{
    keepRunning = 0;
}

int main(int argc, char **argv)
{
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    OatppComponents::PORT = 8080;

    oatpp::Environment::init();
    {
        OatppComponents components;
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler, "http");
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

        router->addController(std::make_shared<WebSocketService>());

        oatpp::network::Server server(connectionProvider, connectionHandler);
        const int              DOMAIN_ID = 0;
        std::cout << "Server starting on http://0.0.0.0:" << OatppComponents::PORT << std::endl;

        auto running = [&]() -> bool { return keepRunning == 1; };

        server.run(running);
    }

    oatpp::Environment::destroy();

    return 0;
}
