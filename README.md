# terminal-rain

[![License](https://img.shields.io/badge/License-MIT-green)](https://github.com/Oakamoore/terminal-rain/blob/main/LICENSE) [![ftxui](https://img.shields.io/badge/FTXUI-5.0.0-orange)](https://github.com/ArthurSonzogni/FTXUI)

## Overview 

A terminal based rain visualisation, inspired by *nkleemann's* [implementation](https://github.com/nkleemann/ascii-rain) in C. 

<p align="center">
	<img src="https://github.com/user-attachments/assets/ff29d010-3487-4202-8ebf-b144b468fe8b">
</p>

## Installation

1. Clone this project

```shell
git clone https://github.com/Oakamoore/terminal-rain.git
```

2. Step into the repository

```shell
cd terminal-rain
```

3. Build the project using [CMake](https://cmake.org/)

```shell
# Configure the build
cmake -S . -B build

# Build project binaries 
cmake --build build
```

### Specifying a Build Configuration

Depending on the type of [CMake generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) being used, a build configuration (`Debug`, `Release` etc.) can be specified as follows:

#### Single Configuration Generator 

```shell
# Configure a release build
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release

# Build release binaries
cmake --build build
```

#### Multi-Configuration Generator

```shell
# Configure the build
cmake -S . -B build 

# Build release binaries
cmake --build build --config Release
```

### Disabling Testing

To prevent tests from being built, append `-D ENABLE_TESTING=0` to the build configuration command.

## Usage 

Once the project is built, navigate to the newly created `terminal-rain/build/` directory, locate the executable, then run the program using:

```shell
./terminal-rain
```

Press `Escape` or `q` while the program is running to quit.

## Testing

[![Catch2](https://img.shields.io/badge/Catch2-3.6.0-orange)](https://github.com/catchorg/Catch2/tree/devel)

Once the project is built, navigate to `terminal-rain/build/tests/`, locate the testing executable, then run the tests using:

```shell
./terminal-rain-tests
```

## Notes

To function as expected, this program requires a terminal emulator that supports a 16-color palette and ANSI escape codes.
