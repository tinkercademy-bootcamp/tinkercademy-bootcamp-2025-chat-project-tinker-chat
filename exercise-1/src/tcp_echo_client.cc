#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <cerrno>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>

int main(int argc, char* argv[]) {
  // #Question - are these the same type?
  // no, first is std::string and the second is cstring.
  std::string message = "Hello from client";
  if(argc>1) {
    message = argv[1];
  }
  const int kPort = 8080;
  const std::string kHostname = "ip-172-31-18-95";
  // const std::string kServerAddress = "::1";
  // sockaddr_in6 address;
  const int kBufferSize = 1024;
  char buffer[kBufferSize] = {0};
  // Creating socket file descriptor
  // int my_sock = socket(AF_INET6, SOCK_STREAM, 0);
  // if (my_sock < 0) {
  //   std::cerr << "Socket creation erron\n";
  //   return -1;
  // }
  // address.sin6_family = AF_INET6;
  // address.sin6_port = htons(kPort);
  // // Convert IPv4 and IPv6 addresses from text to binary form
  // if (inet_pton(AF_INET6, kServerAddress.c_str(), &address.sin6_addr) <= 0) {
  //   std::cerr << "Invalid address/ Address not supported\n";
  //   return -1;
  // }
  // // Connect to the server
  // if (connect(my_sock, (sockaddr *)&address, sizeof(address)) < 0) {
  //   std::cerr << "Connection Failed\n";
  //   return -1;
  // }

  struct addrinfo hints{}, *res;
  hints.ai_family = AF_INET; // Use IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP socket
  if(getaddrinfo(kHostname.c_str(), std::to_string(kPort).c_str(), &hints, &res) != 0) {
    std::cerr << "getaddrinfo failed\n";
    return -1;
  }
  int my_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (my_sock < 0) {
    std::cerr << "Socket creation error\n";
    freeaddrinfo(res);
    return -1;
  }
  // Connect to the server
  if (connect(my_sock, res->ai_addr, res->ai_addrlen) < 0) {
    std::cerr << "Connection Failed: " << strerror(errno) << "\n";
    freeaddrinfo(res);
    close(my_sock);
    return -1;
  }
  freeaddrinfo(res); // Free the addrinfo structure after use
  // Send message
  send(my_sock, message.c_str(), message.size(), 0);
  std::cout << "Sent: " << message << "\n";
  // Wait for reply
  ssize_t read_size = read(my_sock, buffer, kBufferSize);
  std::cout << "Received: " << buffer << "\n";
  // Close the socket
  close(my_sock);
  return 0;
}