#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

#include <netinet/in.h>
#include <string>
#include <thread>

namespace tt::chat::client {
class Client {
public:
  /*
  Function - Client (Constructor)
  Purpose - Initializes a Client object with the specified port and server address.
  Parameters:
    port - The port number on which the client will connect to the server.
    server_address - The IP address of the server to connect to.
  Returns: A Client object that is ready to connect to the server.
  Throws: std::runtime_error if there is an error in creating the socket or connecting to the server.
  */
  Client(int port, const std::string &server_address);

  /*
  Function - start
  Purpose - Starts the client by launching a thread to handle user input and another thread to receive messages from the server.
  Parameters: None
  Returns: None
  Throws: None
  */
  void start();

  /*
  Function - ~Client (Destructor)
  Purpose - Cleans up resources used by the Client object.
  Parameters: None
  Returns: None
  Throws: None
  Description: This function closes the client socket and stops the receiver thread to release system resources.
  */
  ~Client();


private:
  // Socket file descriptor for the client
  int socket_;

  // A boolean flag to indicate if the client is running
  bool running_ = true;

  // A receiver thread to handle incoming messages
  std::thread receiver_thread_;



  /*
  Function - create_client_socket
  Purpose - Creates a socket for the client to connect to the server.
  Parameters: None
  Returns: Returns a socket file descriptor on success.
  Throws: std::runtime_error if socket creation fails.
  */
  sockaddr_in create_server_address(const std::string &server_ip, int port);

  /*
  Function - connect_to_server
  Purpose - Connects the client socket to the server using the provided address.
  Parameters:
    sock - The socket file descriptor of the client.
    server_address - The sockaddr_in structure containing the server's address and port.
  Returns: None
  Throws: std::runtime_error if the connection to the server fails.
  */
  void connect_to_server(int sock, sockaddr_in &server_address);

  /*
  Function - receive_messages
  Purpose - Continuously receives messages from the server and prints them to the console.
  Parameters: None
  Returns: None
  Throws: std::runtime_error if there is an error in receiving messages.
  */
  void receive_messages();

  /*
  Function - handle_user_input
  Purpose - Continuously reads user input from the console and sends it to the server.
  Parameters: None
  Returns: None
  Throws: std::runtime_error if there is an error in sending messages to the server.
  */
  void handle_user_input();



  // A constant buffer size for receiving messages
  static constexpr int kBufferSize = 1024;
};
} // namespace tt::chat::client

#endif // CHAT_CLIENT_H
