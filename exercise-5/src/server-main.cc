#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "server/server.h"

int main() {
  namespace ttc = tt::chat;
  const int kPort = 8080;

  ttc::server::Server server(kPort);
  server.start();

  return 0;
}
