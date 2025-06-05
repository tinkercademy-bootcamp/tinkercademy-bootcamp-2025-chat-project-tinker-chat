#ifndef UTILS_H
#define UTILS_H

#include <concepts>
#include <stdexcept>
#include <string_view>

#include "spdlog/spdlog.h"

namespace tt::chat {

/*
* Function: check_error
* Purpose: Checks a condition and throws an error with a message if the condition is true.
* Parameters:
*   test - A boolean condition to check.
*   error_message - A message to log and include in the exception if the condition is true.
* Throws:
*   std::runtime_error - If the condition is true, an exception is thrown with the provided error message.
*/
template <std::same_as<bool> T, std::convertible_to<std::string_view> S>
void check_error(T test, S error_message) {
  if (test) {
    SPDLOG_ERROR("{}", error_message);
    throw std::runtime_error(error_message);
  }
}

} // namespace tt::chat

#endif // UTILS_H
