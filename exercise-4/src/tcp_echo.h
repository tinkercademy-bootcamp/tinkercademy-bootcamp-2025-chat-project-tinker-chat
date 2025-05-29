#ifndef TCP_ECHO_H
#define TCP_ECHO_H

#include <string>
#include <cstdint>

constexpr uint16_t ECHO_PORT = 12345;

constexpr size_t ECHO_BUFFER_SIZE = 1024;

template <typename T, typename S> void check_error(T test, S error_message);
int create_socket();
#endif