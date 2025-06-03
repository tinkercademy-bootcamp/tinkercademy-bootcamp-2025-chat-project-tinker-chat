#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

#include <netinet/in.h>
#include <string>
#include <thread>

namespace tt::chat::client {
class Client {
public:
  Client(int port, const std::string &server_address);
  void start();
  ~Client();

private:
  int socket_;
  bool running_ = true;
  std::thread receiver_thread_;
  sockaddr_in create_server_address(const std::string &server_ip, int port);
  void connect_to_server(int sock, sockaddr_in &server_address);
  void receive_messages();
  void handle_user_input();

  static constexpr int kBufferSize = 1024;
};
} // namespace tt::chat::client

#endif // CHAT_CLIENT_H
