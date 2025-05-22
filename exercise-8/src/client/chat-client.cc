#include "chat-client.h"
#include "../net/chat-sockets.h"
#include "../utils.h"

tt::chat::client::ChatClient::ChatClient(int port, const std::string &ip_str)
    : socket_{tt::chat::net::create_socket()} {
  using namespace tt::chat;
  sockaddr_in address = net::create_address(ip_str, port);
  auto err_code = connect(socket_, (sockaddr *)&address, sizeof(address));
  check_error(err_code < 0, "Connection Failed.\n");
  epoll_fd_ = epoll_create(kEpollMaxFD);
}

void tt::chat::client::ChatClient::handle_connections() {

  epoll_event events[kEpollMaxEvents];
  net::epoll_ctl(EPOLL_CTL_ADD, epoll_fd_, socket_, EPOLLIN | EPOLLET);

  for (;;) {
    char in_buffer[kBufferSize] = {0};

    printf("input: ");
    fgets(in_buffer, sizeof(in_buffer), stdin);
    auto c = strlen(in_buffer) - 1;
    in_buffer[c] = '\0';
    write(socket_, in_buffer, c + 1);

    memset(in_buffer, 0, sizeof(in_buffer));
    ssize_t bytes_read = 0;
    auto queued_event_count =
        epoll_wait(epoll_fd_, events, kEpollMaxEvents, -1);
    check_error(queued_event_count == -1, "epoll_wait() error\n");
    SPDLOG_INFO("queued_event_count: {}", queued_event_count);
    for (int i = 0; i < queued_event_count; i++) {
      if (events[i].events & EPOLLIN) {
        memset(in_buffer, 0, sizeof(in_buffer));
        bytes_read = read(socket_, in_buffer, sizeof(in_buffer));
        check_error(bytes_read == -1, "read() error\n");
        SPDLOG_INFO("msg: {}\n", in_buffer);
      }
    }
  }
}

tt::chat::client::ChatClient::~ChatClient() {
  close(socket_);
  close(epoll_fd_);
}
