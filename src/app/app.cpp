#include "app.h"

#include <iostream>

#include "../loader/loader.h"
#include "../command/command.h"
#include "../utils/path.h"
#include "../utils/colors.h"
#include "../runner/runner.h"

namespace app {
  int run_nyd(const std::vector<std::string>& arguments, const std::string& yamlConfig) {
    if (arguments.empty()) {
      std::cerr << "Usage: nyd <command> [subcommand...]\n"; // send usage example
      return 1; // exit with error status
    }
  
    // Load YAML and create the Command tree
    std::vector<Command> topLevelCommands = loadCommandTree(utils::expandTilde(yamlConfig));
    // Find the command
    const Command* matchedCommand = resolveCommand(topLevelCommands, arguments);
    // if no command is matched
    if (!matchedCommand) {
      std::cerr << "Exiting, no command input match\n";
      return 1;
    }
    // And finally, execute the found command!
    std::cout << CLR_GOLD << "⚠ WARNING: " << CLR_PURPLE << "nydus v0.0.1 " << CLR_LIME << "has spawned!" << CLR_RESET << "\n";
    runner::executeCommand(matchedCommand);
    return 0;
  }
}
