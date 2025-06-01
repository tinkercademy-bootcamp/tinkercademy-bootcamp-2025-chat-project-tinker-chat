#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../net/chat-sockets.h"
#include "../utils.h"
#include "server.h"

namespace tt::chat::server {
Server::Server(int port) : port_(port), sock_(create_server_socket()) {
  create_server_address(port);
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
}