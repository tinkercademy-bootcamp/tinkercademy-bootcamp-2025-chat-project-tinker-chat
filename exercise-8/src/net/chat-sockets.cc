#include "chat-sockets.h"

int tt::chat::net::create_socket() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  tt::chat::check_error(sock < 0, "Socket creation error");
  return sock;
}

sockaddr_in tt::chat::net::create_address(int port) {
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  return address;
}

sockaddr_in tt::chat::net::create_address(const std::string &ip, int port) {
  auto address = create_address(port);
  auto error_code = inet_pton(AF_INET, ip.c_str(), &address.sin_addr);
  check_error(error_code <= 0, "Invalid address/ Address not supported\n");
  return address;
}

int tt::chat::net::set_non_blocking(int sock) {
  auto flags = fcntl(sock, F_GETFL, 0);
  check_error(flags == -1, "fcntl() error");
  auto error_code = fcntl(sock, F_SETFL, flags | O_NONBLOCK);
  check_error(error_code == -1, "fcntl() error");
  return sock;
}

/*
 * register events of fd to epfd
 */
void tt::chat::net::epoll_ctl(int state, int epoll_fd, int fd,
                              uint32_t events) {
  epoll_event ev{};
  ev.events = events;
  ev.data.fd = fd;
  auto error_code = epoll_ctl(epoll_fd, state, fd, &ev);
  check_error(error_code == -1, "epoll_ctl() error");
}