#ifndef CLIENT_INFO_H
#define CLIENT_INFO_H

#include <string>
namespace tt::chat::server {
struct ClientInfo {
    int fd;
    std::string username;
    std::string current_channel;
    ClientInfo(int fd) : fd(fd), username(""), current_channel("general") {}
};
}

#endif