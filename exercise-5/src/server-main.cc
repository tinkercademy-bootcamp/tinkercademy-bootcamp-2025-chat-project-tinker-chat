#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "net/chat-sockets.h"
// #include "utils.h"
#include "../server/server.h"
namespace tt::chat::server {

void set_socket_options(int sock, int opt) {
  namespace ttc = tt::chat;
  auto err_code = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                             &opt, sizeof(opt));
  if (err_code < 0) {
    std::cerr << "setsockopt() error\n";
    exit(EXIT_FAILURE);
  }
}

int create_server_socket() {
  int sock = net::create_socket();
  set_socket_options(sock, 1);
  return sock;
}

void bind_address_to_socket(int sock, sockaddr_in &address) {
  namespace ttc = tt::chat;
  auto err_code = bind(sock, (sockaddr *)&address, sizeof(address));
  if (err_code < 0) {
    std::cerr << "bind failed\n";
    exit(EXIT_FAILURE);
  }
}

void listen_on_socket(int sock) {
  namespace ttc = tt::chat;
  auto err_code = listen(sock, 3);
  if (err_code < 0) {
    std::cerr << "listen failed\n";
    exit(EXIT_FAILURE);
  }
}

void handle_accept(int sock) {
  namespace ttc = tt::chat;
  const int kBufferSize = 1024;
  char buffer[kBufferSize] = {0};
  ssize_t read_size = read(sock, buffer, kBufferSize);
 
  if (read_size < 0) {
    std::cerr << "Read error on client socket " << sock << "\n";
    close(sock);
    exit(EXIT_FAILURE);
  }
  if (read_size > 0) {
    std::cout << "Received:" << buffer << "\n";
    send(sock, buffer, read_size, 0);
    std::cout << "Echo message sent\n";
  } else if (read_size == 0) {
    std::cout << "Client disconnected.\n";
  }
  close(sock);
}
 
sockaddr_in create_server_address(int port) {
  namespace ttn = tt::chat::net;
  sockaddr_in address = ttn::create_address(port);
  address.sin_addr.s_addr = INADDR_ANY;
  return address;
}
 
void handle_connections(int sock, sockaddr_in &address) {
  socklen_t address_size = sizeof(address);

  while (true) {
    int accepted_socket = accept(sock, (sockaddr *)&address, &address_size);
    if (accepted_socket < 0) {
      std::cerr << "Accept error\n";
      exit(EXIT_FAILURE);
    }
    handle_accept(accepted_socket);
  }
}

} // namespace tt::chat::server

int main() {
  // namespace ttc = tt::chat;
  // const int kPort = 8080;

  // int my_socket = ttc::server::create_server_socket();
  // sockaddr_in address = ttc::server::create_server_address(kPort);

  // // start listening on the socket
  // ttc::server::bind_address_to_socket(my_socket, address);
  // ttc::server::listen_on_socket(my_socket);

  // std::cout << "Server listening on port " << kPort << "\n";
  // ttc::server::handle_connections(my_socket, address);
  // close(my_socket);

  // return 0;
  tt::chat::Server server(8080);
  server.run();
  return 0;
}
