#!/usr/bin/env bash
set -e

INCLUDE_VSCODE=false
REFRESH_BUILD_DIR=false
BUILD_TYPE="Release"
BUILD_DIR="build"

# Parse arguments
for arg in "$@"; do
  case $arg in
    --vscode)
      INCLUDE_VSCODE=true
      shift
      ;;
    --debug)
      BUILD_TYPE="Debug"
      shift
      ;;
    --refresh)
      REFRESH_BUILD_DIR=true
      shift
      ;;
    *)
      echo "Usage: ./bootstrap.sh [--vscode] [--debug] [--refresh]"
      exit 1
      ;;
  esac
done

# Clean and recreate build directory
if [ "$REFRESH_BUILD_DIR" = true ]; then
  rm -rf "$BUILD_DIR"
  mkdir -p "$BUILD_DIR"
fi

# Run conan install into build/$BUILD_TYPE
echo "Setting up Conan + CMake environment..."
conan install . \
  --build=missing \
  --profile:host=default \
  --profile:build=default \
  --settings=build_type="$BUILD_TYPE" \
  --generator=CMakeToolchain \
  --generator=CMakeDeps

cmake -B "$BUILD_DIR/$BUILD_TYPE" -S . \
  -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
  -DCMAKE_TOOLCHAIN_FILE="$BUILD_DIR/$BUILD_TYPE/generators/conan_toolchain.cmake"

# Optional VSCode setup
if [ "$INCLUDE_VSCODE" = true ]; then
  ln -sf "$BUILD_DIR/$BUILD_TYPE/compile_commands.json" compile_commands.json

  if [ ! -f .vscode/settings.json ]; then
    mkdir -p .vscode
    cat > .vscode/settings.json <<EOL
{
  "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools",
  "C_Cpp.default.compileCommands": "\${workspaceFolder}/compile_commands.json",
  "cmake.buildDirectory": "\${workspaceFolder}/$BUILD_DIR/$BUILD_TYPE"
}
EOL
    echo "VSCode settings initialized."
  fi
fi

echo "Environment bootstrapped!"
