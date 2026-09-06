#pragma once

/// @file fwd.h
///
/// @brief Форвадная декларация.
///

#include <memory>

class Session; 
using SessionWeakPtr = std::weak_ptr< Session >;