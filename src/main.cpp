#include <iostream>
#include <vector>
#include <string>

#include "loader/loader.h"
#include "command/command.h"
#include "runner/runner.h"


int main(int argc, char** argv) {
  if (argc < 2) { // if not enough args to resolve
    std::cerr << "Usage: nyd <command> [subcommand...]\n"; // send usage example
      return 1; // exit with error status
  }

  // Parse CLI args as a string vector
  std::vector<std::string> arguments(argv + 1, argv + argc); // make from the 2nd arg (argv + 1) to the end of the array (argv + argc)

  // Load YAML and create the Command tree
  std::vector<Command> topLevelCommands = loadCommandTree("~/.nydus.yaml");
  // TODO: I'm not sure tilde works like this, we'll see

  // Find the command
  const Command* matchedCommand = resolveCommand(topLevelCommands, arguments);
  
  // And finally, execute the found command!
  runner::executeCommand(matchedCommand);

  return 0;
}
