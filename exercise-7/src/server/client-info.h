#ifndef CLIENT_INFO_H
#define CLIENT_INFO_H

#include <string>
namespace tt::chat::server {
struct ClientInfo {
    int fd;
    std::string username;
    std::string current_channel;
    ClientInfo() : fd(-1), username(""), current_channel("general") {}  // default constructor
    ClientInfo(int fd) : fd(fd), username(""), current_channel("general") {}
};
}

#endif