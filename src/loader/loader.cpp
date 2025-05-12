#include "loader.h"
#include <iostream>

Command parseCommandNode(const YAML::Node& node) {
  // YAML validation
  if (!node["name"] || !node["name"].IsScalar()) {
    throw std::runtime_error("Missing or invalid 'name' field");
  }
  if (!node["argument"] || !node["argument"].IsScalar()) {
    throw std::runtime_error("Missing or invalid 'argument' field");
  }
  if (node["commands"] && !node["commands"].IsSequence()) {
    throw std::runtime_error("'commands' must be a list");
  }

  // Assign YAML data to command object
  Command command;
  // safely pull the values out of the YAML nodes using the safeGet helper function
  command.name = safeGet<std::string>(node, "name");
  command.argument = safeGet<std::string>(node, "argument");
  command.cd = safeGet<std::string>(node, "cd");
  command.pre = safeGet<std::string>(node, "pre");
  command.exec = safeGet<std::string>(node, "exec");

  if (node["commands"]) {
    command.subcommands.emplace(); // Initialize the optional field
    // for every child command listed
    for (const YAML::Node& child : node["commands"]) {
      command.subcommands->push_back(parseCommandNode(child)); // add the child node to the end of the subcommands vector
    }
  }
  return command; // send back the fully initialized command instance
}

std::vector<Command> loadCommandTree(const std::string& filepath) {
  YAML::Node root = YAML::LoadFile(filepath); // create the YAML node tree from the filepath
  const YAML::Node& list = root["commands"]; // grab top level key "commands"
  std::vector<Command> topLevelCommands; // create an empty collection to house the top-level command nodes
  // for every immediate child node in the root "commands" list
  for (const YAML::Node node: list) {
    topLevelCommands.push_back(parseCommandNode(node)); // add each top level node/project to the end of the top level vector
  }
  return topLevelCommands; // send back the final collection of top level commands
}
