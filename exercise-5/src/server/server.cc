#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../net/chat-sockets.h"
#include "../utils.h"
#include "server.h"

namespace tt::chat::server {
Server::Server(int port) : port_(port), sock_(net::create_socket()) {
  create_server_address(port);
  set_socket_options(sock_);
  bind_address_to_socket();
  listen_on_socket();
}
void Server::create_server_address(int port) {
  server_address_ = net::create_address(port);
  server_address_.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
}
void Server::bind_address_to_socket() {
  auto err_code = bind(sock_, (sockaddr *)&server_address_, sizeof(server_address_));
  check_error(err_code < 0, "bind failed\n");
}
void Server::listen_on_socket() {
  auto err_code = listen(sock_, 3);
  check_error(err_code < 0, "listen failed\n");
  std::cout << "Server listening on port " << port_ << "\n";
}
void Server::handle_accept(int client_sock) {
  char buffer[1024] = {0};
  ssize_t read_size = read(client_sock, buffer, sizeof(buffer));
  check_error(read_size < 0, "Read error on client socket " + std::to_string(client_sock));
  
  if (read_size > 0) {
    std::cout << "Received: " << buffer << "\n";
    send(client_sock, buffer, read_size, 0);
    std::cout << "Echo message sent\n";
  } else if (read_size == 0) {
    std::cout << "Client disconnected.\n";
  }
  
  close(client_sock);
}
void Server::set_socket_options(int sock) {
  int opt_val = 1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val)) < 0) {
    perror("setsockopt failed");
  }
}
void Server::start() {
    socklen_t address_size = sizeof(server_address_);
  while (true) {
    int client_sock = accept(sock_, (sockaddr *)&server_address_, &address_size);
    check_error(client_sock < 0, "Accept error\n");
    handle_accept(client_sock);
  }
}
Server::~Server() {
  close(sock_);
  std::cout << "Server socket closed.\n";
}
}