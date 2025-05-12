#include "loader.h"
#include <iostream>

Command parseCommandNode(const YAML::Node& node) {
  Command command;
  command.name = safeGet<std::string>(node, "name");
  command.argument = safeGet<std::string>(node, "argument");
  command.cd = safeGet<std::string>(node, "cd");
  command.pre = safeGet<std::string>(node, "pre");
  command.exec = safeGet<std::string>(node, "exec");

  if (node["commands"]) {
    command.subcommands.emplace(); // Initialize the optional field

    for (const YAML::Node& child : node["commands"]) {
      command.subcommands->push_back(parseCommandNode(child));
    }
  }

  return command;
}

std::vector<Command> loadCommandTree(const std::string& filepath) {
  YAML::Node root = YAML::LoadFile(filepath);
  const YAML::Node& list = root["commands"];

  std::vector<Command> topLevelCommands;

  for (const YAML::Node node: list) {
    topLevelCommands.push_back(parseCommandNode(node));
  }

  return topLevelCommands;
}
