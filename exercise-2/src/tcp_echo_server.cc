#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

const int kBufferSize = 1024;

void check_error(bool test, std::string error_message) {
  if (test) {
    std::cerr << error_message << "\n";
    exit(EXIT_FAILURE);
  }
}

int create_socket() {
  int my_sock=socket(AF_INET, SOCK_STREAM, 0);
  check_error(my_sock<0,"Socket creation error\n");
  return my_sock;
}

bool set_socket_options(int sock, int opt) {
  auto errorflag=setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt));
  check_error(errorflag<0,"setsockopt() error\n");
  close(sock);
  return true;
}

sockaddr_in create_address(int port) {
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  return address;
}

void bind_address_to_socket(int sock, sockaddr_in &address) {
  auto errorflag=bind(sock, (sockaddr *)&address, sizeof(address));
  check_error(errorflag<0,"bind failed\n");
  close(sock);
}

void listen_on_socket(int sock) {
  auto errorflag=listen(sock,3);
  check_error(errorflag<0,"listen failed\n");
    close(sock);
 
}

void start_listening_on_socket(int my_socket, sockaddr_in &address) {
  const int kSocketOptions = 1;
  set_socket_options(my_socket, kSocketOptions);

  bind_address_to_socket(my_socket, address);
  listen_on_socket(my_socket);
}

void handle_accept(int client_socket) {
  char buffer[kBufferSize] = {0};
  ssize_t valread = read(client_socket, buffer, kBufferSize);

  if (valread > 0) {
    std::cout << "Received: " << buffer << "\n";
    send(client_socket, buffer, valread, 0);
    std::cout << "Echo message sent\n";
  } else if (valread == 0) {
    std::cout << "Client disconnected.\n";
  } else {
    std::cerr << "Read error on client socket " << client_socket << "\n";
  }
  close(client_socket);
}

void handle_connections(int sock, int port) {
  sockaddr_in address = create_address(port);
  socklen_t address_size = sizeof(address);

  // #Question - is it good to have an infinite loop?
  // Yes , server needs to keep waiting for clients need to join and communicate
  while (true) {
    int accepted_socket = accept(sock, (sockaddr *)&address, &address_size);
    if (accepted_socket < 0) {
      std::cerr << "accept error\n";
      // we continue to accept new connections if possible
      continue;
    }
    handle_accept(accepted_socket);
  }
}

int main() {
  const int kPort = 8080;
  int my_socket = create_socket();
  sockaddr_in address = create_address(kPort);

  // #Question - is there a better name for this function?
  // Seems fine 
  start_listening_on_socket(my_socket, address);
  std::cout << "Server listening on port " << kPort << "\n";
  handle_connections(my_socket, kPort);
  close(my_socket);

  return 0;
}