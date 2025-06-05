#ifndef CHAT_SOCKETS_H
#define CHAT_SOCKETS_H

#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../utils.h"

namespace tt::chat::net {

/*
Function: create_socket
Purpose: Creates a socket for communication.
Return Value: Returns a socket file descriptor on success.
Throws: std::runtime_error if socket creation fails.
*/
int create_socket();

/*
Function: create_address
Purpose: Creates a sockaddr_in structure for the specified port.
Parameters:
  port - The port number to bind the socket to.
Return Value: Returns a sockaddr_in structure with the specified port and INADDR_ANY address.
Throws: None
*/
sockaddr_in create_address(int port);

} // namespace tt::chat::net

#endif // CHAT_SOCKETS_H
