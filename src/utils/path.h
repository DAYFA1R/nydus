#pragma once

#include <filesystem>
#include <string>

namespace utils {
  std::filesystem::path expandTilde(const std::string& rawPath);
}
