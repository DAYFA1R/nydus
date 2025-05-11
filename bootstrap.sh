#!/usr/bin/env bash
set -e

INCLUDE_VSCODE=false
BUILD_DIR="build"

# Parse arguments
for arg in "$@"; do
  case $arg in
    --vscode)
      INCLUDE_VSCODE=true
      shift
      ;;
    *)
      echo "Usage: ./bootstrap.sh [--vscode]"
      exit 1
      ;;
  esac
done

echo "Setting up Conan + CMake environment..."

# Clean and recreate build directory
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"

# Run conan install into build/Release
conan install . \
  --build=missing \
  --profile:host=default \
  --profile:build=default \
  --settings=build_type=Release \
  --generator=CMakeToolchain \
  --generator=CMakeDeps

# Run cmake preset from root, NOT inside build dir
cmake --preset conan-release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Optional VSCode setup
if [ "$INCLUDE_VSCODE" = true ]; then
  ln -sf "$BUILD_DIR/Release/compile_commands.json" compile_commands.json

  if [ ! -f .vscode/settings.json ]; then
    mkdir -p .vscode
    cat > .vscode/settings.json <<EOL
{
  "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools",
  "C_Cpp.default.compileCommands": "\${workspaceFolder}/compile_commands.json",
  "cmake.buildDirectory": "\${workspaceFolder}/build/Release"
}
EOL
    echo "VSCode settings initialized."
  fi
fi

echo "Environment bootstrapped!"