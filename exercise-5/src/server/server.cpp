#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../net/chat-sockets.h"
#include "../utils.h"
#include "server.h"

namespace tt::chat::server {
Server::Server(int port) : port_(port), sock_(create_server_socket()) {
  create_server_address(port);
  bind_address_to_socket();
  listen_on_socket();
}
}