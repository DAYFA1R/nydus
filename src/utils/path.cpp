#include "path.h"

#include <cstdlib>
#include <iostream>

namespace utils {
  std::filesystem::path expandTilde(const std::string& rawPath) {
    // if the path exists and its first character is '~'
    if (!rawPath.empty() && rawPath[0] == '~') {
      const char* home = std::getenv("HOME"); // safely get the env var
      // if no home variable
      if (!home) {
        throw std::runtime_error("HOME variable is not set but was attempted to be used via '~'."); // throw since its impossible to continue
      }
      return std::filesystem::path(std::string(home) + rawPath.substr(1)); // join the path of the home env variable to the path after the '~' is removed
    }
    return std::filesystem::path(rawPath); // otherwise its an absolute path (it better be), and just let 'er rip
  }
}
