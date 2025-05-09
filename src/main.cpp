#include <iostream>
#include <yaml-cpp/yaml.h>

int main() {
    YAML::Node config = YAML::Load("{name: Conan, type: Package}");
    std::cout << "Name: " << config["name"].as<std::string>() << "\n";
    std::cout << "blep \n";
    return 0;
}
