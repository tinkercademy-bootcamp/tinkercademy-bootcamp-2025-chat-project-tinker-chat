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
  /*
  Function: Server (Constructor)
  Purpose: Initializes a Server object with the specified port.
  Parameters:
    port - The port number on which the server will listen for incoming connections.
  Returns: A Server object that is ready to handle connections.
  Throws: std::runtime_error if there is an error in creating the socket, binding, or listening.
  */
  Server(int port);

  /*
  Function: ~Server (Destructor)
  Purpose: Cleans up resources used by the Server object.
  Parameters: None
  Returns: None
  Throws: None
  Description: This function closes the server socket and the epoll file descriptor to release system resources.
  */
  ~Server();

  /*
  Function: handle_connections
  Purpose: Handles incoming client connections and processes their messages.
  Parameters: None
  Returns: None
  Throws: std::runtime_error if there is an error in accepting connections or processing messages.
  Description: This function runs an event loop that waits for incoming connections and messages from clients.
  */
  void handle_connections();

  
private:

  // Socket file descriptor for the server
  int socket_;

  // Address structure for the server socket
  sockaddr_in address_;

  // File descriptor for the epoll instance
  int epoll_fd_;

  // A map to store client file descriptors and their associated ClientInfo
  std::unordered_map<int, ClientInfo> clients_;

  // A map to store channels and their associated client file descriptors
  std::unordered_map<std::string, std::set<int>> channels_;

  // A constant buffer size for receiving messages
  static constexpr int kBufferSize = 1024;

  // Maximum number of events to handle in a single epoll wait
  static constexpr int kMaxEvents = 1000; //can be changed



  /*
  Function: handle_accept
  Purpose: Accepts a new client connection and adds it to the epoll instance.
  Parameters:
    sock - The socket file descriptor for the server.
  Returns: None
  Throws: std::runtime_error if the accept operation fails.
  */
  void handle_accept(int sock);

  /*
  Function: handle_client_message
  Purpose: Handles incoming messages from a client.
  Parameters:
    client_fd - The file descriptor of the client.
  Returns: None
  Throws: None
  */
  void handle_client_message(int client_fd);

  /*
  Function: process_message
  Purpose: Processes a message received from a client.
  Parameters:
    client_fd - The file descriptor of the client.
    msg - The message received from the client.
  Returns: None
  Throws: None
  Description: This function checks if the message is a command (starts with '/') or a regular message.
  */
  void process_message(int client_fd, const std::string& msg);

  /*
  Function: handle_command
  Purpose: Handles commands sent by the client.
  Parameters:
    client - The ClientInfo object containing client details.
    tokens - A vector of strings containing the command and its arguments.
  Returns: None
  Throws: None
  Description: This function processes commands like setting username, joining channels, leaving channels, and creating channels.
  */
  void handle_command(ClientInfo& client, std::vector<std::string>& tokens);

  /*
  Function: broadcast_to_channel
  Purpose: Broadcasts a message to all clients in a specific channel.
  Parameters:
    channel - The name of the channel to which the message will be sent.
    msg - The message to be broadcasted.
    sender_fd - The file descriptor of the client who sent the message (optional, default is -1).
  Returns: None
  Throws: None
  Description: This function sends the message to all clients in the specified channel, except for the sender.
  */
  void broadcast_to_channel(const std::string& channel, const std::string& msg, int sender_fd = -1);

  /*
  Function: set_socket_options
  Purpose: Sets socket options for the given socket file descriptor.
  Parameters:
    sock - The socket file descriptor.
    opt - The option to set (e.g., SO_REUSEADDR).
  Returns: None
  Throws: std::runtime_error if setting socket options fails.
  Description: This function sets the specified socket options to allow the server to reuse the address and port.
  */
  static void set_socket_options(int sock, int opt);

  /*
  Function: make_socket_non_blocking
  Purpose: Sets the given socket file descriptor to non-blocking mode.
  Parameters:
    sfd - The socket file descriptor to set to non-blocking mode.
  Returns: 0 on success, -1 on failure.
  Throws: None
  Description: This function modifies the socket's file descriptor flags to make it non-blocking, allowing the server to handle multiple connections without blocking on I/O operations.
  */
  static int make_socket_non_blocking(int sfd);

  /*
  Function: split_message
  Purpose: Splits a message into tokens based on whitespace.
  Parameters:
    msg - The message to be split.
  Returns: A vector of strings containing the tokens.
  Throws: None
  Description: This function takes a message string and splits it into individual tokens based on whitespace characters. It returns a vector of strings containing the tokens.
  */
  std::vector<std::string> split_message(const std::string& msg);

};
} // namespace tt::chat::server

#endif // CHAT_SERVER_H
