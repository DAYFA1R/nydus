#include "command.h"

#include <iostream>

// Matches args to an actual command in the tree
const Command* resolveCommand(const std::vector<Command>& commands, const std::vector<std::string>& arguments) {
  const Command* currentCommand = nullptr; // default to no command found
  const std::vector<Command>* currentLevel = &commands; // set the currentLevel as the parsed command vector
  
  // for each argument provided in the CLI
  for (const std::string& argument : arguments) {
    bool matched = false; // set default state (because we haven't found anything yet)
    // look at the current command
    for (const Command& command : *currentLevel) {
      // if the command is this one
      if (command.name == argument || command.argument == argument) {https://github.com/DAYFA1R/nydus/tree/main/.github/workflows
        currentCommand = &command; // set the current command to this one
        matched = true; // because we totally found it!
        // now, if there are child commands
        if (command.subcommands.has_value()) {
          currentLevel = &command.subcommands.value(); // set the currentLevel to the value of the subcommands vector
        } else {
          currentLevel = nullptr; // otherwise set the currentLevel to nullptr since we don't need to keep going deeper
        }
        break; // leave the loop since something matched
      }
    }
    // if we didn't find jack
    if (!matched) {
      std::cout << "✗ No match found for: " << argument << "\n";
      return nullptr; // send back a nullptr
    }

    if (currentLevel == nullptr) {
      break; // stop processing further arguments
    }
  }
  return currentCommand; // otherwise send back the successfully found command
}
