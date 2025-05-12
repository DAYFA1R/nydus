#pragma once

#include <string>
#include <vector>
#include <optional>

// Data representation of what could exist in a YAML node
struct Command {
  std::string name; // this might be superfluous, but adding it for now
  std::string argument; // shorthand cmd (eg. nyd <argument>)
  std::optional<std::string> cd; // where does it execute
  std::optional<std::string> exec; // what does it execute
  std::optional<std::string> pre; // pre-exection status
  std::optional<std::vector<Command>> subcommands; // reference to children, default to empty vector if no descendents
};

// A fun recursive dive through the command hierarchy pulled out of our YAML
const Command* resolveCommand(const std::vector<Command>& commands, const std::vector<std::string>& arguments);
