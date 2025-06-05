// server-utils.cc
#include "command-utils.h"

#include <sys/socket.h>
#include <unistd.h>
#include <sstream>

namespace tt::chat::server::commands {

void send_message(int fd, const std::string& msg) {
  send(fd, msg.c_str(), msg.size(), 0);
}

bool is_valid_args(const std::vector<std::string>& tokens, size_t expected_count) {
  return tokens.size() >= expected_count;
}

bool channel_exists(const std::string& name, const std::unordered_map<std::string, std::set<int>>& channels) {
  return channels.find(name) != channels.end();
}

void move_client_to_channel(ClientInfo& client, const std::string& new_channel,
                            std::unordered_map<std::string, std::set<int>>& channels) {
  channels[client.current_channel].erase(client.fd);
  channels[new_channel].insert(client.fd);
  client.current_channel = new_channel;
}

bool try_create_channel(const std::string& name,
                        std::unordered_map<std::string, std::set<int>>& channels) {
  if (channel_exists(name, channels)) return false;
  channels[name] = std::set<int>();
  return true;
}


std::vector<std::string> split_message(const std::string &msg) {
  std::vector<std::string> tokens;
  std::istringstream stream(msg);
  std::string token;
  while (stream >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

} // namespace tt::chat::server
