#ifndef CLIENT_INFO_H
#define CLIENT_INFO_H

#include <string>
namespace tt::chat::server {
struct ClientInfo {
    // File descriptor for the client connection
    int fd;

    // Username of the client
    std::string username;

    /*
    Current channel the client is connected to
    Default channel is "general"
    */
    std::string current_channel;



    /*
    Function: ClientInfo (Constructor)
    Purpose: Initializes a ClientInfo object with default values.
    Parameters: None
    Returns: A ClientInfo object with default values.
    */
    ClientInfo() : fd(-1), username(""), current_channel("general") {}

    /*
    Function: ClientInfo (Constructor with file descriptor)
    Purpose: Initializes a ClientInfo object with a specific file descriptor.
    Parameters:
    - fd: The file descriptor for the client connection.
    Returns: A ClientInfo object with the specified file descriptor and default values for username and current_channel.
    */
    ClientInfo(int fd) : fd(fd), username(""), current_channel("general") {}
};
}

#endif // CLIENT_INFO_H
