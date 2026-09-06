
#include "data_manager.h"
#include "rc.h"
#include <string>
#include <utility>

ReturnCodes DataManager::Insert( const std::string& table, const int id, const std::string name )
{
    auto it = tables_.find( table );
    if ( it == tables_.end() )
    {
        return ReturnCodes::TableNotExists;
    }

    auto& target = it->second;
    auto [ iterator, success ] = target.emplace( id, name );
    if ( !success )
    {
        return ReturnCodes::RecordAlreadyExists;
    }
    return ReturnCodes::Ok;
}

ReturnCodes DataManager::Truncate( const std::string& table )
{
    auto it = tables_.find( table );
    if ( it == tables_.end() )
    {
        return ReturnCodes::TableNotExists;
    }
    auto& target = it->second;
    target.clear();
    return ReturnCodes::Ok;
}

ReturnCodes DataManager::Intersection( std::map< int, std::pair< std::string , std::string > >& result )
{
    for ( const auto& [ id, nameA ] : tableA_ )
    {
        auto it = tableB_.find( id );
        if ( it != tableB_.end() )
        {
            result.emplace( id, std::make_pair( nameA, it->second ) );
        }
    }
    return ReturnCodes::Ok;
}

ReturnCodes DataManager::SymmetricDifference( std::map< int, std::pair< std::string , std::string > >& result )
{
    for ( const auto& [ id, name ] : tableA_ )
    {
        if ( tableB_.find( id ) == tableB_.end() )
        {
            result.emplace( id, std::make_pair( name, std::string{} ) );
        }
    }

    for ( const auto& [ id, name ] : tableB_ )
    {
        if ( tableA_.find( id ) == tableA_.end() )
        {
            result.emplace( id, std::make_pair( std::string{}, name ) );
        }
    }

    return ReturnCodes::Ok;
}
