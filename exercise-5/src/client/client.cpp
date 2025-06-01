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
void Client::connectToServer() {
  auto err_code = connect(sock_, (sockaddr*)&server_address_, sizeof(server_address_));
  check_error(err_code < 0, "Connection Failed.\n");
}
void Client::send_and_receive_message(const std::string& message) {
  const int kBufferSize = 1024;
  char recv_buffer[kBufferSize] = {0};

  // Send the message to the server
  send(sock_, message.c_str(), message.size(), 0);
  std::cout << "Sent: " << message << "\n";

  // Receive response from the server
  ssize_t read_size = read(sock_, recv_buffer, kBufferSize);
  check_error(read_size < 0, "Read error.\n");
  if (read_size > 0) {
    std::cout << "Received: " << recv_buffer << "\n";
  } else if (read_size == 0) {
    std::cout << "Server closed connection.\n";
  }
}
}