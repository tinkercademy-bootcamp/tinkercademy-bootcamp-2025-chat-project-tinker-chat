#ifndef CHAT_SOCKETS_H
#define CHAT_SOCKETS_H

#include <arpa/inet.h>
#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../utils.h"

namespace tt::chat::net {

int create_socket();

sockaddr_in create_address(int port);

sockaddr_in create_address(const std::string &ip, int port);

int set_non_blocking(int sock);

void epoll_ctl(int state, int epfd, int fd, uint32_t events);

} // namespace tt::chat::net

#endif // CHAT_SOCKETS_H
