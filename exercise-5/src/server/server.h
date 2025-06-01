#ifndef TT_CHAT_SERVER_H
#define TT_CHAT_SERVER_H

#include<iostream>
#include <netinet/in.h>

namespace tt::chat::server {
class Server {
public:
    Server(int port);
    ~Server();
    void start();
private:
    int port_;
    int sock_;
    sockaddr_in server_address_;

    void create_server_address(int port);
    void bind_address_to_socket();
    void listen_on_socket();
    void handle_accept(int client_sock);
    void set_socket_options(int opt);
};
}
#endif