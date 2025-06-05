#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>

#include "spdlog/spdlog.h"

#include "commands/command-handler.h"
#include "commands/command-utils.h"
#include "chat-server.h"
#include "../net/chat-sockets.h"
#include "../utils.h"
#include "socket-utils.h"


tt::chat::server::Server::Server(int port)
    : socket_(tt::chat::net::create_socket()),
      address_(tt::chat::net::create_address(port)) {
  using namespace tt::chat;
  tt::chat::server::set_socket_options(socket_, 1);

  address_.sin_addr.s_addr = INADDR_ANY;

  auto err_code = bind(socket_, (sockaddr *)&address_, sizeof(address_));
  check_error(err_code < 0, "bind failed\n");

  err_code = listen(socket_, 3);
  check_error(err_code < 0, "listen failed\n");

  make_socket_non_blocking(socket_);
  epoll_fd_ = epoll_create1(0);
  epoll_event event = {EPOLLIN, {.fd = socket_}};
  err_code = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, socket_, &event);
  channels_["general"] = std::set<int>();

  std::cout << "Server listening on port " << port << "\n";
}

tt::chat::server::Server::~Server() {
  close(socket_);
  close(epoll_fd_);
}

void tt::chat::server::Server::handle_connections() {
  epoll_event events[kMaxEvents];
  while (true) {
    int ready_fds = epoll_wait(epoll_fd_, events, kMaxEvents, -1);
    for (int i = 0; i < ready_fds; i++) {
      if (events[i].data.fd == socket_) {
        handle_accept(socket_);
      } else {
        handle_client_message(events[i].data.fd);
      }
    }
  }
}

void tt::chat::server::Server::handle_accept(int sock) {
  using namespace tt::chat::server;

  sockaddr_in client_address;
  socklen_t client_address_len = sizeof(client_address);
  int client_fd = accept(sock, (sockaddr *)&client_address, &client_address_len);
  if (client_fd < 0) {
    SPDLOG_ERROR("Accept failed");
    return;
  }
  make_socket_non_blocking(client_fd);
  epoll_event event = {EPOLLIN, {.fd = client_fd}};
  int err_code = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, client_fd, &event);
  if (err_code < 0) {
    SPDLOG_ERROR("epoll_ctl failed");
    close(client_fd);
    return;
  }
  clients_[client_fd] = ClientInfo(client_fd);
  channels_["general"].insert(client_fd);
  commands::send_message(client_fd, "Welcome to the chat server! You are in the 'general' channel. You can set your username using /username command\n");
  SPDLOG_INFO("New client connected: fd = {}", client_fd);
}

void tt::chat::server::Server::handle_client_message(int client_fd) {
  char buffer[kBufferSize] = {0};
  ssize_t msg_length = recv(client_fd, buffer, kBufferSize - 1, 0);
  if (msg_length <= 0) {
    channels_[clients_[client_fd].current_channel].erase(client_fd);
    clients_.erase(client_fd);
    close(client_fd);
    SPDLOG_INFO("Client disconnected: fd = {}", client_fd);
    return;
  }
  buffer[msg_length] = '\0';
  process_message(client_fd, std::string(buffer, msg_length));
}

void tt::chat::server::Server::process_message(int client_fd, const std::string &msg) {
  auto &client = clients_[client_fd];
  std::vector<std::string> tokens = commands::split_message(msg);
  if (tokens.empty()) return;

  if (tokens[0][0] == '/') {
    tt::chat::server::commands::handle_command(client, tokens, channels_);
  } else {
    std::string channel_name = client.current_channel;
    broadcast_to_channel(channel_name, client.username + ": " + msg + "\n", client_fd);
  }
}

void tt::chat::server::Server::broadcast_to_channel(const std::string &channel, const std::string &msg, int sender_fd) {
  for (int client_fd : channels_[channel]) {
    if (client_fd != sender_fd) {
      commands::send_message(client_fd, msg);
    }
  }
}
