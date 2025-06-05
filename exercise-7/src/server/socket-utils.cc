#include "socket-utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>

namespace tt::chat::server {

int make_socket_non_blocking(int sfd) {
  int flags = fcntl(sfd, F_GETFL, 0);
  if (flags == -1) {
    perror("fcntl get");
    return -1;
  }
  flags |= O_NONBLOCK;
  if (fcntl(sfd, F_SETFL, flags) == -1) {
    perror("fcntl set");
    return -1;
  }
  return 0;
}

void set_socket_options(int sock, int opt) {
  int err_code = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                            &opt, sizeof(opt));
  if (err_code < 0) {
    perror("setsockopt");
    throw std::runtime_error("setsockopt() failed");
  }
}

}  // namespace tt::chat::net
