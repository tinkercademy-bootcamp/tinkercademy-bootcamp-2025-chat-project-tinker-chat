#pragma once

namespace tt::chat::server {

/*
  Function: make_socket_non_blocking
  Purpose: Sets a socket to non-blocking mode.
  Parameters:
    sfd - The socket file descriptor.
  Returns: 0 on success, -1 on failure.
  Throws: None
*/
int make_socket_non_blocking(int sfd);

/*
  Function: set_socket_options
  Purpose: Enables socket options like SO_REUSEADDR and SO_REUSEPORT.
  Parameters:
    sock - The socket file descriptor.
    opt - The option value to set.
  Returns: void
  Throws: std::runtime_error on failure
*/
void set_socket_options(int sock, int opt);

}  // namespace tt::chat::net
