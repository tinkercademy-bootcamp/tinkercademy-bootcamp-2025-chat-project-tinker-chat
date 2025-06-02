#ifndef CLIENT_INFO_H
#define CLIENT_INFO_H

#include <string>

struct ClientInfo {
    int fd;
    std::string username;
    std::string current_channel;
};

#endif