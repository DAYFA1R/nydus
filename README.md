# `nydus` [![Release Binaries](https://github.com/DAYFA1R/nydus/actions/workflows/release.yaml/badge.svg)](https://github.com/DAYFA1R/nydus/actions/workflows/release.yaml) [![Build passing](https://github.com/DAYFA1R/nydus/actions/workflows/ci.yaml/badge.svg?branch=main)](https://github.com/DAYFA1R/nydus/actions/workflows/ci.yaml) [![codecov](https://codecov.io/gh/DAYFA1R/nydus/graph/badge.svg?token=KEPS4OGVYM)](https://codecov.io/gh/DAYFA1R/nydus)
> **a YAML-powered CLI aliasing tool for project commands**

 `nydus` is a YAML-powered CLI aliasing tool that lets developers define shortcut commands for common project tasks — like install, build, and run — that can be executed from anywhere on your system.

## Install
### Direct download
[![Download macOS](https://img.shields.io/badge/download-macOS-lightgrey)](https://github.com/DAYFA1R/nydus/releases/latest/download/nydus-macos-latest.tar.gz) [![Download Ubuntu](https://img.shields.io/badge/download-ubuntu-orange)](https://github.com/DAYFA1R/nydus/releases/latest/download/nydus-ubuntu-latest.tar.gz)

### curl
Make sure you replace `<YOUR OS>` with either `macos` or `ubuntu`
```
curl -L https://github.com/DAYFA1R/nydus/releases/download/v1.0.0/nydus-<YOUR OS>-latest.tar.gz | tar xz
sudo mv nyd /usr/local/bin/
```

### Compile from source
Scroll down to the "Development" section

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

## Development
### Setup
**Pre-requisites**
- Install the `conan` package manager (to install the `yaml-cpp` dep)
- You need `cmake` & `make`
- From the repo root: `chmod +x bootstrap.sh`

#### Build & run from source (for actual use)
- run `./bootstrap.sh` (it defaults to Release build without any additional flags provided)
- run `cmake --build ./build/Release`
- run `./build/Release/nyd` OR `mv` the binary to a `/bin` directory

#### Build & run from source (for development)
- run `./bootstrap.sh --debug`
  - you can add `--refresh` to auto delete the old build folder if you're regenerating the build often
> ⚠️ For fellow VS Code enthusiasts:
> if you want OOTB intellisense support so that VS Code doesn't shit its pants over `yaml-cpp` not being found,
> you can optionally pass in a --vscode flag to the setup script like:
> `./bootstrap.sh --vscode` :\)
- run `cmake --build ./build/Debug`
- run `./build/Debug/nyd`


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
