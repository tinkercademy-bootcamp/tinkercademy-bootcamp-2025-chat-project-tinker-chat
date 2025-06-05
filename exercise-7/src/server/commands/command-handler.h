// command-handler.h
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <set>

#include "../chat-server.h"

namespace tt::chat::server::commands {

// Dispatcher
/*
Function: handle_command
Purpose: Handles commands sent by the client.
Parameters:
  client - The ClientInfo object containing client details.
  tokens - A vector of strings containing the command and its arguments.
  channels - A map of channel names to sets of client file descriptors.
Returns: None
Throws: None
*/
void handle_command(ClientInfo& client,
                    std::vector<std::string>& tokens,
                    std::unordered_map<std::string, std::set<int>>& channels);

// Individual command functions
/*
Function: command_username
Purpose: Sets the username for the client.
Parameters:
  client - The ClientInfo object containing client details.
  tokens - A vector of strings containing the command and its arguments.
Returns: None
Throws: None
*/
void command_rename(ClientInfo& client, const std::vector<std::string>& tokens);

/*
Function: command_join
Purpose: Joins a channel for the client.
Parameters:
  client - The ClientInfo object containing client details.
  tokens - A vector of strings containing the command and its arguments.
  channels - A map of channel names to sets of client file descriptors.
Returns: None
Throws: None
*/
void command_join(ClientInfo& client, const std::vector<std::string>& tokens,
                  std::unordered_map<std::string, std::set<int>>& channels);

/*
Function: command_leave
Purpose: Leaves the current channel for the client.
Parameters:
  client - The ClientInfo object containing client details.
  channels - A map of channel names to sets of client file descriptors.
Returns: None
Throws: None
*/
void command_leave(ClientInfo& client,
                   std::unordered_map<std::string, std::set<int>>& channels);

/*
Function: command_list
Purpose: Lists all available channels and their members.
Parameters:
  fd - The file descriptor of the client to whom the list will be sent.
  channels - A map of channel names to sets of client file descriptors.
Returns: None
Throws: None
*/
void command_list(int fd, const std::unordered_map<std::string, std::set<int>>& channels);

/*
Function: command_create
Purpose: Creates a new channel with the given name.
Parameters:
  client - The ClientInfo object containing client details.
  tokens - A vector of strings containing the command and its arguments.
  channels - A map of channel names to sets of client file descriptors.
Returns: None
Throws: None
*/
void command_create(ClientInfo& client, const std::vector<std::string>& tokens,
                    std::unordered_map<std::string, std::set<int>>& channels);

/*
Function: command_exit
Purpose: Exits the chat server for the client.
Parameters:
  client - The ClientInfo object containing client details.
Returns: None
Throws: None
*/
void command_exit(ClientInfo& client);

} // namespace tt::chat::server
