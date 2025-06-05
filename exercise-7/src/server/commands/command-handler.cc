// command-handler.cc
#include "command-handler.h"
#include "command-utils.h"

#include <unistd.h>

namespace tt::chat::server::commands {

void handle_command(ClientInfo& client,
                    std::vector<std::string>& tokens,
                    std::unordered_map<std::string, std::set<int>>& channels) {
  const std::string& command = tokens[0];

  if (command == "/username") {
    command_username(client, tokens);
  } else if (command == "/join") {
    command_join(client, tokens, channels);
  } else if (command == "/leave") {
    command_leave(client, channels);
  } else if (command == "/list") {
    command_list(client.fd, channels);
  } else if (command == "/create") {
    command_create(client, tokens, channels);
  } else if (command == "/exit") {
    command_exit(client);
  } else {
    send_message(client.fd, "Unknown command\n");
  }
}

void command_username(ClientInfo& client, const std::vector<std::string>& tokens) {
  if (!is_valid_args(tokens, 2)) {
    send_message(client.fd, "Usage: /username <your_username>\n");
    return;
  }
  client.username = tokens[1];
  send_message(client.fd, "Username set to " + client.username + "\n");
}

void command_join(ClientInfo& client, const std::vector<std::string>& tokens,
                  std::unordered_map<std::string, std::set<int>>& channels) {
  if (!is_valid_args(tokens, 2)) {
    send_message(client.fd, "Usage: /join <channel_name>\n");
    return;
  }
  const std::string& name = tokens[1];
  if (!channel_exists(name, channels)) {
    send_message(client.fd, "Channel does not exist. Use /create to make one.\n");
    return;
  }
  move_client_to_channel(client, name, channels);
  send_message(client.fd, "Joined channel: " + name + "\n");
}

void command_leave(ClientInfo& client, std::unordered_map<std::string, std::set<int>>& channels) {
  const std::string& current = client.current_channel;
  channels[current].erase(client.fd);
  move_client_to_channel(client, "general", channels);
  send_message(client.fd, "Left current channel. You're now in 'general'.\n");
}

void command_list(int fd, const std::unordered_map<std::string, std::set<int>>& channels) {
  std::string result = "Available channels:\n";
  for (const auto& pair : channels) {
    result += pair.first + "\n";
  }
  send_message(fd, result);
}

void command_create(ClientInfo& client, const std::vector<std::string>& tokens,
                    std::unordered_map<std::string, std::set<int>>& channels) {
  if (!is_valid_args(tokens, 2)) {
    send_message(client.fd, "Usage: /create <channel_name>\n");
    return;
  }
  const std::string& name = tokens[1];
  if (!try_create_channel(name, channels)) {
    send_message(client.fd, "Channel already exists.\n");
    return;
  }
  move_client_to_channel(client, name, channels);
  send_message(client.fd, "Channel " + name + " created and joined.\n");
}

void command_exit(ClientInfo& client) {
  close(client.fd);
}

} // namespace tt::chat::server
