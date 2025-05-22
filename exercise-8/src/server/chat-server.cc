#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_set>

#include "spdlog/spdlog.h"

#include "../net/chat-sockets.h"
#include "../utils.h"
#include "chat-server.h"

tt::chat::server::Server::Server(int port)
    : socket_(tt::chat::net::create_socket()),
      address_(tt::chat::net::create_address(port)) {
  using namespace tt::chat;

  int opt = 1;
  auto err_code = setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                             &opt, sizeof(opt));
  check_error(err_code < 0, "setsockopt() error\n");

  address_.sin_addr.s_addr = INADDR_ANY;

  err_code = bind(socket_, (sockaddr *)&address_, sizeof(address_));
  check_error(err_code == -1, "bind failed\n");

  err_code = tt::chat::net::set_non_blocking(socket_);

  err_code = listen(socket_, kMaxConnections);
  check_error(err_code == -1, "listen failed\n");

  std::cout << "Server listening on port " << port << "\n";
}

tt::chat::server::Server::~Server() { close(socket_); }

void tt::chat::server::Server::handle_connections() {
  char in_buffer[kBufferSize];

  sockaddr_in client_address{};
  epoll_event events[kMaxEpollEvents]{};

  auto my_fd = epoll_create(1);
  // net::epoll_ctl(EPOLL_CTL_ADD, my_fd, socket_, EPOLLIN | EPOLLOUT |
  // EPOLLET);
  net::epoll_ctl(EPOLL_CTL_ADD, my_fd, socket_, EPOLLIN | EPOLLET);

  std::unordered_set<decltype(my_fd)> connected_fds;
  socklen_t socklen = sizeof(client_address);
  for (;;) {
    auto queued_event_count = epoll_wait(my_fd, events, kMaxEpollEvents, -1);
    check_error(queued_event_count == -1, "epoll_wait() error\n");

    for (int i = 0; i < queued_event_count; i++) {
      if (events[i].data.fd == socket_) {
        /* handle new connection */
        auto connected_sock =
            accept(socket_, (struct sockaddr *)&client_address, &socklen);

        auto error_code = inet_ntop(AF_INET, (char *)&(client_address.sin_addr),
                                    in_buffer, sizeof(client_address));
        check_error(error_code == nullptr, "inet_ntop() error");

        SPDLOG_INFO("connected with {}:{} on {}", in_buffer,
                    ntohs(client_address.sin_port), connected_sock);

        net::set_non_blocking(connected_sock);
        net::epoll_ctl(EPOLL_CTL_ADD, my_fd, connected_sock,
                       EPOLLIN | EPOLLET | EPOLLRDHUP | EPOLLHUP);
        connected_fds.insert(connected_sock);

      } else if (events[i].events & EPOLLIN) {
        /* handle EPOLLIN event */
        for (;;) {
          memset(in_buffer, 0, sizeof(in_buffer));
          auto chars_read =
              read(events[i].data.fd, in_buffer, sizeof(in_buffer));
          if (chars_read <= 0 /* || errno == EAGAIN */) {
            break;
          } else {
            SPDLOG_INFO("message: {}", in_buffer);
            for (auto &fd : connected_fds) {
              // if (fd != events[i].data.fd) {
              write(fd, in_buffer, strlen(in_buffer));
              // }
            }
          }
        }
      } else {
        SPDLOG_WARN("unexpected");
      }
      /* check if the connection is closing */
      if (events[i].events & (EPOLLRDHUP | EPOLLHUP)) {
        auto my_fd = events[i].data.fd;
        SPDLOG_INFO("connection {} closed", my_fd);
        epoll_ctl(my_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
        connected_fds.erase(events[i].data.fd);
        close(events[i].data.fd);
        continue;
      }
    }
  }
}

void tt::chat::server::Server::set_socket_options(int sock, int opt) {
  using namespace tt::chat;
  auto err_code = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                             &opt, sizeof(opt));
  check_error(err_code < 0, "setsockopt() error\n");
}
