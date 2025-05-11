#include <iostream>
#include <yaml-cpp/yaml.h>

int main() {
    // Find and load YAML

    // Traverse YAML and create Segment tree

    // Parse args and map to Segments
    

    //placeholder to test YAML lib
    YAML::Node config = YAML::Load("{name: Conan, type: Package}");
    std::cout << "Name: " << config["name"].as<std::string>() << "\n";
    std::cout << "blep \n";
    return 0;
}
