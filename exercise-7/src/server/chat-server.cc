#include <unistd.h>
#include <sys/epoll.h>

#include "spdlog/spdlog.h"

#include "../net/chat-sockets.h"
#include "../utils.h"
#include "chat-server.h"

tt::chat::server::Server::Server(int port)
    : socket_(tt::chat::net::create_socket()),
      address_(tt::chat::net::create_address(port)) {
  using namespace tt::chat;
  set_socket_options(socket_, 1);

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

tt::chat::server::Server::~Server() { close(socket_); close(epoll_fd_);}

void tt::chat::server::Server::handle_connections() {
  epoll_event events[kMaxEvents];

  while (true) {
    int ready_fds = epoll_wait(epoll_fd_, events, kMaxEvents, -1);

    for(int i = 0; i < ready_fds; i++){
      if(events[i].data.fd == socket_){
        handle_accept(socket_); // If the event is on the listening socket, accept a new connection
      }
      else {
        // handle_client_message(events[i].data.fd); // Handle messages from clients
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
  std::string welcome_msg = "Welcome the the chat server! You are in the 'general' channel. You can set your username using /username command\n";
  send(client_fd, welcome_msg.c_str(), welcome_msg.size(), 0);
  SPDLOG_INFO("New client connected: fd = {}", client_fd);
}

int tt::chat::server::Server::make_socket_non_blocking(int sfd) {
    int flags = fcntl(sfd, F_GETFL, 0);
    if (flags == -1) return -1;
    flags |= O_NONBLOCK;
    return fcntl(sfd, F_SETFL, flags);
}

void tt::chat::server::Server::handle_client_message(int client_fd){
  char buffer[kBufferSize] = {0};
  ssize_t msg_length = recv(client_fd, buffer, kBufferSize - 1, 0);
  if(msg_length <= 0){
    channels_["general"].erase(client_fd);
    clients_.erase(client_fd);
    close(client_fd);
    SPDLOG_INFO("Client disconnected: fd = {}", client_fd);
    return;
  }
  buffer[msg_length] = '\0';
  process_message(client_fd, std::string(buffer, msg_length));
}

void tt::chat::server::Server::process_message(int client_fd, const std::string& msg) {
  auto& client = clients_[client_fd];
  std::vector<std::string> tokens = split_message(msg);
  if (tokens.empty()) {
    return; // An empty message is not processed (but it's not an error)
  }
  if(tokens[0][0] == '/') {
    handle_command(client, tokens);
    return;
  }
  std::string channel_name = clients_[client_fd].current_channel;
  broadcast_to_channel(channel_name, clients_[client_fd].username + ": " + msg + "\n", client_fd);
}

void tt::chat::server::Server::handle_command(ClientInfo& client, std::vector<std::string>& tokens) {
  if(tokens[0] == "/username") {
    if(tokens.size() < 2) {
      send(client.fd, "Usage: /username <your_username>\n", 33, 0);
      return;
    }
    client.username = tokens[1];
    send(client.fd, ("Username set to " + client.username + "\n").c_str(), client.username.size() + 17, 0);
  } else if(tokens[0] == "/join") {
    if(tokens.size() < 2) {
      send(client.fd, "Usage: /join <channel_name>\n", 28, 0);
      return;
    }
    std::string channel_name = tokens[1];
    if(channels_.find(channel_name) == channels_.end()) {
      send(client.fd, ("Channel " + channel_name + " does not exist. You can create it by using /create command.\n").c_str(), channel_name.size() + 45, 0);
      return;
    }
    channels_[channel_name].insert(client.fd);
    client.current_channel = channel_name;
    broadcast_to_channel(channel_name, client.username + " has joined the channel.\n", client.fd);
    send(client.fd, ("Joined channel: " + channel_name + "\n").c_str(), channel_name.size() + 16, 0);
  } else if(tokens[0] == "/leave") {
    channels_[client.current_channel].erase(client.fd);
    client.current_channel = "general";
    send(client.fd, "Left current channel. You are now in 'general' channel.\n", 56, 0);
  } else if(tokens[0] == "/list") {
    std::string channel_list = "Available channels:\n";
    for(const auto& channel : channels_) {
      channel_list += channel.first + "\n";
    }
    send(client.fd, channel_list.c_str(), channel_list.size(), 0);
  } else if(tokens[0] == "/create") {
    if(tokens.size() < 2) {
      send(client.fd, "Usage: /create <channel_name>\n", 30, 0);
      return;
    }
    std::string channel_name = tokens[1];
    if(channels_.find(channel_name) != channels_.end()) {
      send(client.fd, ("Channel " + channel_name + " already exists.\n").c_str(), channel_name.size() + 25, 0);
      return;
    }
    channels_[channel_name] = std::set<int>();
    channels_[channel_name].insert(client.fd);
    client.current_channel = channel_name;
    send(client.fd, ("Channel " + channel_name + " created and joined.\n").c_str(), channel_name.size() + 31, 0);
  }
  else if(tokens[0] == "/exit") {
    close(client.fd);
    clients_.erase(client.fd);
    channels_[client.current_channel].erase(client.fd);
    SPDLOG_INFO("Client disconnected: fd = {}", client.fd);
  }
  else {
    send(client.fd, "Unknown command\n", 16, 0);
  }
}