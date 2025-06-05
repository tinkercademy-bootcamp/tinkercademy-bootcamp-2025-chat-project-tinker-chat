// command-handler.h
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <set>

#include "../chat-server.h"

namespace tt::chat::server::commands {

// Dispatcher
void handle_command(ClientInfo& client,
                    std::vector<std::string>& tokens,
                    std::unordered_map<std::string, std::set<int>>& channels);

// Individual command functions
void command_username(ClientInfo& client, const std::vector<std::string>& tokens);
void command_join(ClientInfo& client, const std::vector<std::string>& tokens,
                  std::unordered_map<std::string, std::set<int>>& channels);
void command_leave(ClientInfo& client,
                   std::unordered_map<std::string, std::set<int>>& channels);
void command_list(int fd, const std::unordered_map<std::string, std::set<int>>& channels);
void command_create(ClientInfo& client, const std::vector<std::string>& tokens,
                    std::unordered_map<std::string, std::set<int>>& channels);
void command_exit(ClientInfo& client);

} // namespace tt::chat::server
