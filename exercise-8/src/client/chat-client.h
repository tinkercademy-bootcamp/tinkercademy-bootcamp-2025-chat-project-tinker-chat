#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

#include <netinet/in.h>
#include <string>

namespace tt::chat::client {
class ChatClient {
public:
  ChatClient(int port, const std::string &server_address);
  ~ChatClient();

  void handle_connections();

private:
  int socket_;
  int epoll_fd_;
  sockaddr_in create_server_address(const std::string &server_ip, int port);

  static constexpr int kBufferSize = 1024;
  static constexpr int kEpollMaxFD = 256;
  static constexpr int kEpollMaxEvents = 1024;
};
} // namespace tt::chat::client

#endif // CHAT_CLIENT_H
