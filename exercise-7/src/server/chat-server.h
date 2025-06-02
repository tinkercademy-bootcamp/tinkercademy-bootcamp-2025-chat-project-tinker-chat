#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <netinet/in.h>
#include <unordered_map>
#include <set>
#include <vector>
#include "client-info.h"
namespace tt::chat::server {

class Server {
public:
  Server(int port);
  ~Server();
  void handle_connections();

private:
  int socket_;
  sockaddr_in address_;
  int epoll_fd_;
  std::unordered_map<int, ClientInfo> clients_;
  std::unordered_map<std::string, std::set<int>> channels_;

  static constexpr int kBufferSize = 1024;

  void handle_accept(int sock);
  void handle_client_message(int client_fd);
  void process_message(int client_fd, const std::string& msg);
  void broadcast_to_channel(const std::string& channel, const std::string& msg, int sender_fd = -1);
  static void set_socket_options(int sock, int opt);
  static int make_socket_non_blocking(int sfd);
};
} // namespace tt::chat::server

#endif // CHAT_SERVER_H
