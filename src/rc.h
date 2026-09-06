#pragma once
/// @file rc.h
/// 
/// Коды возврата парсера.
///



/// @brief Коды возврата парсера.
enum class ReturnCodes
{
    Ok                      = 0,    /// Успешно.
    InvalidCommand          = 1,    /// Неверная команда.
    InternalError           = 2,    /// Другая ошибка.
    TableNotExists          = 3,    /// Таблицы не существует.
    RecordAlreadyExists     = 4,    /// Запись в таблице уже существует.
};
