#include "runner.h"

#include <filesystem>
#include <cstdlib>
#include <iostream>

#include "../utils/path.h"
#include "../utils/colors.h"

namespace runner {
  void executeCommand(const Command* command) {
    if (!command) {
      std::cerr << "Error: Command is null\n";
      return;
    }
  
    // Change to the current working directory if cd is provided and non-empty
    if (command->cd && !command->cd->empty()) {
      try {
        // deref command, so we can access cd (command->cd), then defer the Optional (*(command->cd)), so we can access the string!
        std::filesystem::path path = utils::expandTilde(*command->cd);
        std::filesystem::current_path(path); // set cd to current path
        std::cout << CLR_GOLD << "→ " << CLR_PURPLE << "Burrowing to: " << CLR_RESET << std::filesystem::current_path() << "\n"; // log dir change
      } catch (const std::filesystem::filesystem_error& error) {
        std::cerr << "Failed to change directory: " << error.what() << "\n"; // log error
        return;
      }
    }
  
    // Run the prefix command if its there
    if (command->pre && !command->pre->empty()) {
      std::cout << CLR_GOLD << "→ " << CLR_PINK << "Moving Overlords: " << CLR_RESET << *command->pre << "\n";
      std::system(command->pre->c_str());
    }
  
    // Run the main command in exec
    if (command->exec && !command->exec->empty()) {
      std::cout << CLR_GOLD << "↳ " << CLR_PINK << "Executing Hivemind directive: " << CLR_RESET << *command->exec << "\n";
      std::system(command->exec->c_str());
    } else {
      std::cout << "No command to execute.\n";
    }
  }
}
