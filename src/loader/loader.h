#pragma once

#include <string>
#include <yaml-cpp/yaml.h>

#include "../command/command.h"

std::vector<Command> loadCommandTree(const std::string& filepath);

// Util helper for safely pulling out YAML fields
template<typename T>
T safeGet(const YAML::Node& node, const std::string key, const T& fallback = T{}) {
  // using a ternary here, but will explain it since I mentally need to do this for generics:
  // if the key exists, then return it as the expected type, otherwise use the fallback
  // * since we are using uniform initialization here, if fallback is not provided
  // * then default to whatever the default constructor for that type is
  return node[key] ? node[key].as<T>() : fallback;
}
