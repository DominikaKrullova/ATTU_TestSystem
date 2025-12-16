#pragma once

#include <oatpp/json/ObjectMapper.hpp>
#include <oatpp/macro/component.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/web/server/AsyncHttpConnectionHandler.hpp>
#include <oatpp/web/server/HttpRouter.hpp>
#include <oatpp/web/server/interceptor/AllowCorsGlobal.hpp>

#include "ClientManager.h"

/**
 *  Class which creates and holds Application components and registers components in oatpp::Environment
 *  Order of components initialization is from top to bottom
 */
class OatppComponents
{
  public:
    static uint16_t PORT;

    /**
     * Create Async Executor
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor)
    (
        []
        {
            return std::make_shared<oatpp::async::Executor>(
                4 /* Data-Processing threads */, 1 /* I/O threads */, 1 /* Timer threads */
            );
        }());

    /**
     *  Create ConnectionProvider component which listens on the port
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)
    (
        []
        {
            return oatpp::network::tcp::server::ConnectionProvider::createShared(
                {"0.0.0.0", OatppComponents::PORT, oatpp::network::Address::IP_4});
        }());

    /**
     *  Create Router component
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)
    ([] { return oatpp::web::server::HttpRouter::createShared(); }());

    /**
     *  Create ConnectionHandler component which uses Router component to route requests
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)
    ("http",
     []
     {
         OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);  // get Router component
         OATPP_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor);        // get Async executor component

         // CORS
         auto connectionHandler = oatpp::web::server::AsyncHttpConnectionHandler::createShared(router, executor);
         connectionHandler->addRequestInterceptor(
             std::make_shared<oatpp::web::server::interceptor::AllowOptionsGlobal>());
         connectionHandler->addResponseInterceptor(
             std::make_shared<oatpp::web::server::interceptor::AllowCorsGlobal>());

         return connectionHandler;
     }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<ClientManager>, clientManager)
    ([] { return std::make_shared<ClientManager>(); }());

    /**
     *  Create websocket connection handler
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, websocketConnectionHandler)
    ("websocket",
     []
     {
         OATPP_COMPONENT(std::shared_ptr<oatpp::async::Executor>, executor);
         OATPP_COMPONENT(std::shared_ptr<ClientManager>, clientManager);
         auto connectionHandler = oatpp::websocket::AsyncConnectionHandler::createShared(executor);
         connectionHandler->setSocketInstanceListener(clientManager);
         return connectionHandler;
     }());

    /**
     *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)
    ([] { return std::make_shared<oatpp::json::ObjectMapper>(); }());
};
