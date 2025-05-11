#pragma once

#include <string>
#include <vector>
#include <memory>

struct Command {
  std::string name; // this might be superfluous, but adding it for now
  std::string argument; // shorthand cmd (eg. nyd <argument>)
  std::string cd; // where does it execute
  std::string exec; // what does it execute
  std::string pre; // pre-exection status
  std::vector<Command> subcommands; // reference to children, default to empty vector if no descendents

  const Command* findSubcommand(const std::string& arg) const; // use the command-line arg to fetch correct sub-command object
};

