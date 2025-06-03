#include <arpa/inet.h>
#include <cstdlib>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "client/chat-client.h"

int main(int argc, char *argv[]) {
  const int kPort = 8080;
  const std::string kServerAddress = "127.0.0.1";

  tt::chat::client::Client client{kPort, kServerAddress};

  client.start();

  return 0;
}
