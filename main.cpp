#include "server/server.h"
#include "handler/handler.h"
#include "dataManager/data_manager.h"
#include <exception>
#include <memory>
#include <string>
#include <iostream>


int main( int argc, char* argv[] )
{
    if ( argc != 2 )
    {
        std::cout << "You must enter only port\n";
        return 1;
    }

    int port = 2000;
    try 
    {
        port = std::stoi( argv[ 1 ] );
    } 
    catch ( std::exception& e ) 
    {
        std::cout << "Failed to parse port " << e.what() << "\n"; 
        return 1;
    }

    std::cout << "Application is running... ";
    auto manager = std::make_shared< DataManager >();
    auto parser = std::make_shared< Handler >( manager );

    ServerPtr server = std::make_unique< Server >( port, parser );
    server->Start();
    return 0;
}