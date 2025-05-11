# `nydus`: a YAML-powered CLI aliasing tool for project commands

`nydus` is a YAML-powered CLI aliasing tool that lets developers define shortcut commands for common project tasks — like install, build, and run — that can be executed from anywhere on your system.

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
$ nyd nyd i
→ Switching to /home/user/dayfa1r/projects/nydus/
→ Running ./bootstrap.sh
```

## How to install (for use)
Haven't got there yet champ

## How to install (for development)
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
Define your command hierarchy in a YAML list like so:
```
commands:
  - name: "nydus"
    arg: "nyd"
    cd: "/home/user/dayfa1r/projects/nydus/"
    exec: "echo 'These are things I want to run on every command in this project'"
    commands:
      - name: "Install"
        arg: "i"
        exec: "./bootstrap.sh"
```

In this example, you can run `nyd nyd i` from any directory, and it will:
1. Switch to `/home/user/dayfa1r/projects/nydus/`
2. Run `./bootstrap.sh`
