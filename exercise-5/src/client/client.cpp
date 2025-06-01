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
}