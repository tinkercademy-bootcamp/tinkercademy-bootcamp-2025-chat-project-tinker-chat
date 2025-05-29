#ifndef TCP_ECHO_H
#define TCP_ECHO_H

#include<iostream>

template <typename T, typename S> void check_error(T test, S error_message) {
  if (test) {
    std::cerr << error_message << "\n";
    exit(EXIT_FAILURE);
  }
}
int create_socket();
#endif