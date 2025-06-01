#include <string>
#include <arpa/inet.h>
#include <cstdlib>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../net/chat-sockets.h"
#include "../utils.h"
#include "client.h"

namespace tt::chat {
Client::Client(const std::string& server_address, int port)
    : port_(port), sock_(net::create_socket()) {
  create_server_address(server_address, port);
  connectToServer();
}
void Client::create_server_address(const std::string& server_ip, int port) {
  server_address_ = net::create_address(port);
  // Convert the server IP address to a binary format
  auto err_code = inet_pton(AF_INET, server_ip.c_str(), &server_address_.sin_addr);
  check_error(err_code <= 0, "Invalid address/ Address not supported\n");
}
}