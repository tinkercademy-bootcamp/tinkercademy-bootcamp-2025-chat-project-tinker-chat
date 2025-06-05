#include <arpa/inet.h>
#include <cstdlib>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#include "client/chat-client.h"

int main(int argc, char *argv[]) {
  const int kPort = 8080;
  const std::string kServerAddress = "127.0.0.1";

  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <username>\n";
    return EXIT_FAILURE;
  }
  std::string username = argv[1];

  tt::chat::client::Client client{kPort, kServerAddress, username};

  client.start();

  return 0;
}
