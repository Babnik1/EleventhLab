
#include "handler.h"
#include "handler/handler.h"
#include "rc.h"
#include <iostream>
#include <unordered_map>
#include <sstream>

/// @brief Действия.
enum class Actions
{
    INSERT                  = 0,     /// Вставка в таблицу.
    TRUNCATE                = 1,     /// Очистка таблицы.
    INTERSECTION            = 2,     /// Пересечение.
    SYMMETRIC_DIFFERENCE    = 3,     /// Симметрическая разница.
};

/// @brief Мапа коммант и действий.
static const std::unordered_map< std::string, Actions > commands =
{
    { "INSERT",                 Actions::INSERT                 },
    { "TRUNCATE",               Actions::TRUNCATE               },
    { "INTERSECTION",           Actions::INTERSECTION           },
    { "SYMMETRIC_DIFFERENCE",   Actions::SYMMETRIC_DIFFERENCE   },
};

/// @brief Код ошибки в сообщение клиенту.
std::string CodeToString( ReturnCodes rc )
{
    switch ( rc )
    {
        case ReturnCodes::Ok:
            return "OK\n";

        case ReturnCodes::InvalidCommand:
            return "ERROR Invalid command\n";

        case ReturnCodes::TableNotExists:
            return "ERR table not exists\n";

        case ReturnCodes::RecordAlreadyExists:
            return "ERR duplicate\n";

        default:
            return "ERROR Internal error\n";
    }
}

std::string PrepareMessage( std::map< int, std::pair< std::string , std::string > > result )
{
    std::ostringstream oss;
    for ( const auto& [ id, names ] : result )
    {
        oss << id << ',' << names.first << ',' << names.second << '\n';
    }
    oss << "OK\n";
    return oss.str();
}

Handler::Handler( DataManagerPtr manager )
    : manager_{ manager }
{}


std::string Handler::HandleCommand( const std::string& command )
{
    std::string action;
    std::string argument;

    std::istringstream iss( command );

    if ( !( iss >> action ) )
    {
        std::cout << "Failed stream to action\n";
        return CodeToString( ReturnCodes::InvalidCommand );
    }
    

    std::getline( iss, argument );

   if ( !argument.empty() )
    {
        argument.erase( 0, 1 );
    }

    auto it = commands.find( action );

    if ( it == commands.end() )
    {
        std::cout << "There is not command in map: " << action << "\n";
        return CodeToString( ReturnCodes::InvalidCommand );
    }
    ReturnCodes rc = ReturnCodes::InvalidCommand;

    switch ( it->second )
    {
        case Actions::INSERT:
        {
            if ( argument.empty() )
            {
                std::cout << "Arguments is empty\n";
                return CodeToString( ReturnCodes::InvalidCommand );
            }
            int id = 0;
            std::string table;
            std::string name;

            std::istringstream pub( argument );
            pub >> table;
            if ( table.empty() )
            {
                std::cout << "INSERT: Table is missed\n";
                return CodeToString( ReturnCodes::InvalidCommand );
            }

            if ( !( pub >> id ) )
            {
                std::cout << "INSERT: ID is missed or invalid\n";
                return CodeToString( ReturnCodes::InvalidCommand );
            }
            
            pub >> name;
            if ( name.empty() )
            {
                std::cout << "INSERT: Name is missed\n";
                return CodeToString( ReturnCodes::InvalidCommand );
            }
            
            rc = manager_->Insert( table, id, name );
            break;
        }
        case Actions::TRUNCATE:
        {
            if ( argument.empty() )
            {
                std::cout << "Arguments is empty\n";
                return CodeToString( ReturnCodes::InvalidCommand );
            }
            std::string table;
            std::istringstream pub( argument );

            pub >> table;
            if ( table.empty() )
            {
                std::cout << "INSERT: Table is missed\n";
                return CodeToString( ReturnCodes::InvalidCommand );
            }

            rc = manager_->Truncate( table );
            break;
        }
        case Actions::INTERSECTION:
        {
            std::map< int, std::pair< std::string, std::string > > result;
            ReturnCodes rc = manager_->Intersection( result );
            if ( rc != ReturnCodes::Ok )
            {
                return CodeToString( rc );
            }
            return PrepareMessage( result );
        }
        case Actions::SYMMETRIC_DIFFERENCE:
        {
            std::map< int, std::pair< std::string, std::string > > result;
            ReturnCodes rc = manager_->SymmetricDifference( result );
            if ( rc != ReturnCodes::Ok )
            {
                return CodeToString( rc );
            }
            return PrepareMessage( result );
            break;
        }
    }
    
    return CodeToString( rc );
}