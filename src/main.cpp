#include <vector>
#include <string>

#include "app/app.h"

int main(int argc, char** argv) {
  std::vector<std::string> arguments(argv + 1, argv + argc);
  return app::run_nyd(arguments, "~/.nydus.yaml");
}
