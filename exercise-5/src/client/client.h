#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>

namespace tt::chat::client {

class Client {
public:
    Client(const std::string& server_address, int port);
    ~Client();
    void send_and_receive_message(const std::string& message);
private:
    int port_;
    int sock_;
    sockaddr_in server_address_;

    void connectToServer();
    void create_server_address(const std::string &server_ip, int port);
};

} // namespace tt::chat

#endif // CLIENT_H