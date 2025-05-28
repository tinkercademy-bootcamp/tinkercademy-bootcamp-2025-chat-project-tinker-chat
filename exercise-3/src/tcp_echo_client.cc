#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void check_error(bool test, std::string error_message) {
  if (test) {
    std::cerr << error_message << "\n";
    exit(EXIT_FAILURE);
  }
}

int create_socket() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  check_error(sock < 0, "Socket creation error");
  return sock;
}

void set_binary_address(sockaddr_in &address, const std::string &server_ip) {
  int err_code = inet_pton(AF_INET, server_ip.c_str(), &address.sin_addr);
  check_error(err_code <= 0, "Invalid address / Address not supported");
}

sockaddr_in create_address(const std::string &server_ip, int port) {
  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_port = htons(port);

  set_binary_address(address, server_ip);
  return address;
}

void connect_to_server(int sock, sockaddr_in &server_address) {
  auto err_code = connect(sock, (sockaddr *)&server_address, sizeof(server_address));
  check_error(err_code < 0, "Connection Failed");
}

void send_and_receive_message(int sock, const std::string &message) {
  const int kBufferSize = 1024;
  char buffer[kBufferSize] = {0};

  ssize_t sent = send(sock, message.c_str(), message.size(), 0);
  check_error(sent < 0, "Send failed");
  std::cout << "Sent: " << message << "\n";

  ssize_t read_size = read(sock, buffer, kBufferSize);
  check_error(read_size < 0, "Read error");

  if (read_size == 0) {
    std::cout << "Server closed connection.\n";
  } else {
    std::cout << "Received: " << buffer << "\n";
  }
}

std::string read_args(int argc, char *argv[]) {
  check_error(argc < 2, std::string("Usage: ") + argv[0] + " <message>");
  return argv[1];
}

int main(int argc, char *argv[]) {
  const int kPort = 8080;
  const std::string kServerAddress = "127.0.0.1";

  std::string message = read_args(argc, argv);
  int my_socket = create_socket();
  sockaddr_in server_address = create_address(kServerAddress, kPort);

  connect_to_server(my_socket, server_address);
  send_and_receive_message(my_socket, message);
  close(my_socket);

  return 0;
}
