# Project README

## Overview
This project is an interpreter for a custom assembly language called IRVM. The source code consists of several components, including a main entry point `Main.c` and supporting files in the `libs/`, `code/`, and `asm/` directories.

## Features
- **Assembly Language Interpretation**: Compiles and executes a custom assembly language.
- **Multi-platform Support**: Builds and runs on Linux, Windows, and WebAssembly using Emscripten.

## Project Structure

### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- No additional libraries are required for this project.

## Build & Run
The build process is managed by Makefiles specific to each operating system. Below are the steps to build and run the project:

### Linux
```bash
cd <Project>
make -f Makefile.linux all
make -f Makefile.linux exe
```

### Windows
```bash
cd <Project>
make -f Makefile.windows all
make -f Makefile.windows exe
```

### WebAssembly (Emscripten)
```bash
cd <Project>
make -f Makefile.web all
make -f Makefile.web exe
```

# Build Steps

## Linux
To build the project on Linux, navigate to the project directory and run:
```bash
make -f Makefile.linux all
```
This will compile the source code and generate the executable in the `build/` directory.

## Windows
For Windows, use:
```bash
make -f Makefile.windows all
```

## WebAssembly (Emscripten)
To build for WebAssembly, run:
```bash
make -f Makefile.web all
```

# Clean Build
If you need to clean the build artifacts and start fresh, you can use:
```bash
make -f Makefile.(os) clean
make -f Makefile.(os) all
```

Replace `(os)` with `linux`, `windows`, or `web` as appropriate for your target platform.