# `nydus`: a yaml-based aliasing tool for simple and structured context switching

## How to install (for use)
Haven't got there yet champ

## How to install (for development)
### Setup
**Pre-requisites**
- Install the `conan` package manager (to install the `yaml-cpp` dep)
- You need `cmake` & `make`

**Then (from project root):**
- `chmod +x dev.sh`
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
Each project or command can be declared as an element in a yaml list:
```
commands:
  - name: "nydus"
    arg: "nyd"
    cd: "/home/user/dayfa1r/projects/nydus/"
    exec: "echo 'These are things I want to run on every command in this project'"
    commands:
      - name: "Install"
        arg: "i"
        exec: "./bootstrap.sh --vscode"
```

