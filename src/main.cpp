#include <iostream>
#include <vector>
#include <string>

#include "loader/loader.h"
#include "command/command.h"
#include "utils/path.h"
#include "utils/colors.h"
#include "runner/runner.h"


int main(int argc, char** argv) {
  if (argc < 2) { // if not enough args to resolve
    std::cerr << "Usage: nyd <command> [subcommand...]\n"; // send usage example
      return 1; // exit with error status
  }

  // Parse CLI args as a string vector
  std::vector<std::string> arguments(argv + 1, argv + argc); // make from the 2nd arg (argv + 1) to the end of the array (argv + argc)

  // Load YAML and create the Command tree
  std::vector<Command> topLevelCommands = loadCommandTree(utils::expandTilde("~/.nydus.yaml"));

  // Find the command
  const Command* matchedCommand = resolveCommand(topLevelCommands, arguments);
  
  // And finally, execute the found command!
  std::cout << CLR_GOLD << "⚠ WARNING: " << CLR_PURPLE << "nydus v0.0.1 " << CLR_LIME << "has spawned!" << CLR_RESET << "\n";
  runner::executeCommand(matchedCommand);

  return 0;
}
