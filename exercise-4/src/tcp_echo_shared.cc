#include <netinet/in.h>
#include "tcp_echo_shared.h"

int create_socket() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  check_error(sock < 0, "Socket creation error\n");
  return sock;
}


