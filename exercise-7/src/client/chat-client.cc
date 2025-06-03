#include "chat-client.h"
#include "../net/chat-sockets.h"
#include "../utils.h"
#include <arpa/inet.h>

tt::chat::client::Client::Client(int port,
                                         const std::string &server_address)
    : socket_{tt::chat::net::create_socket()}, running_(true) {
  sockaddr_in address = create_server_address(server_address, port);
  connect_to_server(socket_, address);
}

// std::string tt::chat::client::Client::send_and_receive_message(
//     const std::string &message) {
//   using namespace tt::chat;
//   char recv_buffer[kBufferSize] = {0};

//   // Send the message to the server
//   send(socket_, message.c_str(), message.size(), 0);
//   std::cout << "Sent: " << message << "\n";

//   // Receive response from the server
//   ssize_t read_size = read(socket_, recv_buffer, kBufferSize);
//   if (read_size > 0) {
//     return std::string(recv_buffer);
//   } else if (read_size == 0) {
//     return "Server closed connection.\n";
//   } else {
//     return "Read error.\n";
//   }
// }

tt::chat::client::Client::~Client() { 
  std::cout << "Closing client connection...\n";
  running_ = false;
  if (receiver_thread_.joinable()){
    receiver_thread_.join();
  }
  close(socket_);
}

sockaddr_in tt::chat::client::Client::create_server_address(
    const std::string &server_ip, int port) {
  using namespace tt::chat;
  sockaddr_in address = net::create_address(port);
  // Convert the server IP address to a binary format
  auto err_code = inet_pton(AF_INET, server_ip.c_str(), &address.sin_addr);
  check_error(err_code <= 0, "Invalid address/ Address not supported\n");
  return address;
}

void tt::chat::client::Client::connect_to_server(
    int sock, sockaddr_in &server_address) {
  using namespace tt::chat;
  auto err_code =
      connect(sock, (sockaddr *)&server_address, sizeof(server_address));
  check_error(err_code < 0, "Connection Failed.\n");
}

void tt::chat::client::Client::start() {
  receiver_thread_ = std::thread(&Client::receive_messages, this);
  handle_user_input();
}

void tt::chat::client::Client::receive_messages(){
  char buffer[kBufferSize];
  while(running_){
    ssize_t msg_length = recv(socket_, buffer, kBufferSize - 1, 0);
    if(msg_length <= 0){
      SPDLOG_INFO("Disconnected from server.");
      running_ = false;
      break;
    }
    buffer[msg_length] = '\0';
    std::cout << buffer << std::flush;
  }
}

void tt::chat::client::Client::handle_user_input() {
  std::string input;
  while (running_) {
    std::getline(std::cin, input);
    if(!running_ || input.empty()) {
      continue; // Skip empty input
    }
    if (input == "/exit") {
      running_ = false;
      if (send(socket_, input.c_str(), input.size(), 0) < 0) {
        SPDLOG_ERROR("Failed to send message");
        break;
      }
      std::cout << "Exiting chat client...\n";
      close(socket_);
      exit(0);
    }
    if (send(socket_, input.c_str(), input.size(), 0) < 0) {
      SPDLOG_ERROR("Failed to send message");
      break;
    }
  }
}