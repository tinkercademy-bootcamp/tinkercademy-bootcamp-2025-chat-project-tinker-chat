// server-utils.h
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <set>

#include "../chat-server.h"

namespace tt::chat::server::commands {

void send_message(int fd, const std::string& msg);
bool is_valid_args(const std::vector<std::string>& tokens, size_t expected_count);
bool channel_exists(const std::string& name, const std::unordered_map<std::string, std::set<int>>& channels);
void move_client_to_channel(struct ClientInfo& client, const std::string& new_channel,
                            std::unordered_map<std::string, std::set<int>>& channels);
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
