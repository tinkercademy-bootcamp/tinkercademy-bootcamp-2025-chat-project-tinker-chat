// server-utils.h
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <set>

#include "../chat-server.h"

namespace tt::chat::server::commands {

/*
Function: send_message
Purpose: Sends a message to a client.
Parameters:
  fd - The file descriptor of the client to whom the message will be sent.
  msg - The message to be sent.
Returns: None
Throws: None
*/
void send_message(int fd, const std::string& msg);

/*
Function: is_valid_args
Purpose: Checks if the number of arguments in a command is valid.
Parameters:
  tokens - A vector of strings containing the command and its arguments.
  expected_count - The expected number of arguments (including the command itself).
Returns: true if the number of arguments matches the expected count, false otherwise.
Throws: None
*/
bool is_valid_args(const std::vector<std::string>& tokens, size_t expected_count);

/*
Function: channel_exists
Purpose: Checks if a channel with the given name exists.
Parameters:
  name - The name of the channel to check.
  channels - A map of channel names to sets of client file descriptors.
Returns: true if the channel exists, false otherwise.
Throws: None
*/
bool channel_exists(const std::string& name, const std::unordered_map<std::string, std::set<int>>& channels);

/*
Function: move_client_to_channel
Purpose: Moves a client to a new channel.
Parameters:
  client - The ClientInfo object containing client details.
  new_channel - The name of the new channel to which the client will be moved.
  channels - A map of channel names to sets of client file descriptors.
Returns: None
Throws: None
*/
void move_client_to_channel(struct ClientInfo& client, const std::string& new_channel,
                            std::unordered_map<std::string, std::set<int>>& channels);

/*
Function: try_create_channel
Purpose: Attempts to create a new channel with the given name.
Parameters:
  name - The name of the channel to be created.
  channels - A map of channel names to sets of client file descriptors.
Returns: true if the channel was successfully created, false if it already exists.
Throws: None
*/
bool try_create_channel(const std::string& name,
                        std::unordered_map<std::string, std::set<int>>& channels);

/*
Function: split_message
Purpose: Splits a message into tokens based on whitespace.
Parameters:
  msg - The message to be split.
Returns: A vector of strings containing the tokens.
Throws: None
Description: This function takes a message string and splits it into individual tokens based on whitespace characters. It returns a vector of strings containing the tokens.
*/
std::vector<std::string> split_message(const std::string &msg);

} // namespace tt::chat::server
