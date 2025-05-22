#ifndef UTILS_H
#define UTILS_H

#include <errno.h>
#include <stdexcept>

#include "spdlog/spdlog.h"

namespace tt::chat {

template <typename T, typename S> void check_error(T test, S error_message) {
  if (test) {
    SPDLOG_ERROR("errno: {}, {}", errno, error_message);
    throw std::runtime_error(error_message);
  }
}

} // namespace tt::chat

#endif // UTILS_H
