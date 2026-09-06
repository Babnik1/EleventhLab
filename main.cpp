#include "server/server.h"
#include "handler/handler.h"
#include "dataManager/data_manager.h"
#include <memory>
#include <string>
#include <iostream>

constexpr int port = 2000;

int main()
{
    std::cout << "Application is running... ";
    auto manager = std::make_shared< DataManager >();
    auto parser = std::make_shared< Handler >( manager );

    ServerPtr server = std::make_unique< Server >( port, parser );
    server->Start();
    return 0;
}