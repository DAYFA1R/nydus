# `nydus` [![Release Binaries](https://github.com/DAYFA1R/nydus/actions/workflows/release.yaml/badge.svg)](https://github.com/DAYFA1R/nydus/actions/workflows/release.yaml) [![Build passing](https://github.com/DAYFA1R/nydus/actions/workflows/ci.yaml/badge.svg?branch=main)](https://github.com/DAYFA1R/nydus/actions/workflows/ci.yaml) [![codecov](https://codecov.io/gh/DAYFA1R/nydus/graph/badge.svg?token=KEPS4OGVYM)](https://codecov.io/gh/DAYFA1R/nydus)
> **a YAML-powered CLI aliasing tool for project commands**

 `nydus` is a YAML-powered CLI aliasing tool that lets developers define shortcut commands for common project tasks — like install, build, and run — that can be executed from anywhere on your system.

[![Download macOS](https://img.shields.io/badge/download-macOS-lightgrey)](https://github.com/DAYFA1R/nydus/releases/latest/download/nydus-macos-latest.tar.gz) [![Download Ubuntu](https://img.shields.io/badge/download-ubuntu-orange)](https://github.com/DAYFA1R/nydus/releases/latest/download/nydus-ubuntu-latest.tar.gz)

## Install
Make sure you replace `<YOUR OS>` with either `macos` or `ubuntu`
```
curl -L https://github.com/DAYFA1R/nydus/releases/download/v1.0.0/nydus-<YOUR OS>-latest.tar.gz | tar xz
sudo mv nyd /usr/local/bin/
```

## How It Works

1. You define project-specific commands in a YAML file.
2. Each command includes:
   - A name and shorthand alias
   - The working directory it should run from
   - The shell command(s) to execute
3. You run `nyd <alias> <subcommand>` from anywhere in your terminal.
4. `nydus` changes to the target directory and executes the command you've defined.

Example:
```
$ nyd proj1 i
→ Switching to /home/user/dayfa1r/projects/nydus/
→ Running ./bootstrap.sh
```

## How to build from source (for use)
Haven't automated the script yet but you can do this:
- run `./bootstrap.sh`
- build using the generated conan preset via CLI or your IDE
- `mv ./build/Release/nyd` to whatever `\bin` you prefer


## How to build from source (for development)
### Setup
**Pre-requisites**
- Install the `conan` package manager (to install the `yaml-cpp` dep)
- You need `cmake` & `make`

**Then (from project root):**
- `chmod +x bootstrap.sh`
- run `./bootstrap.sh`
> ⚠️ For fellow VS Code enthusiasts:
> if you want OOTB intellisense support so that VS Code doesn't shit its pants over `yaml-cpp` not being found,
> you can optionally pass in a --vscode flag to the setup script like:
> `./bootstrap.sh --vscode` :\)

### Build
- run `cmake --build --preset conan-release`

### Run
- run `./build/Release/nyd`

## Usage
Define your command hierarchy in a YAML list like so, as recursively as you want:
```
commands:
  - name: "Nydus"
    argument: "nydus"
    cd: "/home/user/dayfa1r/projects/nydus/"
    exec: "./bootstrap.sh"

  - name: "Portfolio"
    arg: "dayf"
    commands:
      - name: "Run"
        argument: "r"
        cd: "~/Projects/DAYFA1R/portfolio"
        pre: "nvm use --lts"
        exec: "npm run"
```

In this example, you can run `nyd dayf r` from any directory, and it will:
1. Switch to `/users/dayfa1r/projects/portfolio/`
2. Run `nvm use --lts && npm run`
