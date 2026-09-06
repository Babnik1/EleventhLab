#pragma once

/// @file handler.h
///
/// @brief Обработчик команд.
///

#include <memory>
#include "fwd.h"
#include "rc.h"
#include "dataManager/data_manager.h"

/// @brief Класс обработчика.
class Handler
{
public:

    /// @brief Конструктор.
    /// @param[in] manager Менеджер данных.
    Handler( DataManagerPtr manager );

    /// @brief Обработка команды.
    /// @param[in] command Команда.
    std::string HandleCommand( const std::string& command );
private:

private:
    DataManagerPtr manager_;    /// Обработчик команд.
};

using HandlerPtr = std::shared_ptr< Handler >;