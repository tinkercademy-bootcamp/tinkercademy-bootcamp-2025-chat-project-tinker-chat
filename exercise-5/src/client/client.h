#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>

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