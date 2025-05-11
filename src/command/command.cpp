#include "command.h"

// Lets you pass in a reference to a string, and allows you to get a subcommand by
const Command* Command::findSubcommand(const std::string& argument) const {
  // if this command doesn't have any subcommands
  if (!subcommands.has_value()) {
    return nullptr;
  }
  // looking through each subcommand
  for (const Command& subcommand : subcommands.value()) {
    // matching by the subcommand name OR argument value
    if (subcommand.name == argument || subcommand.argument == argument) {
      // returning a reference to the subcommand if its found
      return &subcommand;
    }
  }
  // or a nullptr if not
  return nullptr;
}
