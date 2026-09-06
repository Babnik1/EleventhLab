#pragma once

/// @file data_manager.h
///
/// @brief Работа с данными.
///


#include <memory>
#include "rc.h"
#include "fwd.h"
#include <map>
#include <unordered_map>

/// @brief Класс работы с данными.
class DataManager
{
public:

    /// @brief Конструктор по умолчанию.
    DataManager() = default;

    /// @brief Вставка в таблицу.
    /// @param[in] table Название таблицы.
    /// @param[in] id Ключ.
    /// @param[in] name Имя.
    ReturnCodes Insert( const std::string& table, const int id, const std::string name );

    /// @brief Очистка таблицы.
    /// @param[in] table Название таблицы.
    ReturnCodes Truncate( const std::string& table );

    /// @brief Пересечение.
    /// @param[out] result Результат.
    ReturnCodes Intersection( std::map< int, std::pair< std::string , std::string > >& result );

    /// @brief Симметричная разница.
    /// @param[out] result Результат.
    ReturnCodes SymmetricDifference( std::map< int, std::pair< std::string , std::string > >& result );

private:
    std::map< int, std::string > tableA_;   /// Мапа А.
    std::map< int, std::string > tableB_;   /// Мапа Б.

    std::unordered_map< std::string, std::map< int, std::string >& > tables_ = /// Мапа мап, для удобства расширения.
    {
        { "A", std::ref( tableA_ ) },
        { "B", std::ref( tableB_ ) },
    };
};

using DataManagerPtr = std::shared_ptr< DataManager >;