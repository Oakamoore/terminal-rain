# terminal-rain

[![License](https://img.shields.io/badge/License-MIT-green)](https://github.com/Oakamoore/terminal-rain/blob/main/LICENSE) [![ftxui](https://img.shields.io/badge/FTXUI-5.0.0-orange)](https://github.com/ArthurSonzogni/FTXUI)

## Overview 

A terminal based rain visualisation, inspired by *nkleemann's* [implementation](https://github.com/nkleemann/ascii-rain) in C. 

<p align="center">
	<img src="https://github.com/user-attachments/assets/ff29d010-3487-4202-8ebf-b144b468fe8b">
</p>

> A terminal emulator that supports a 16 colour palette and ANSI escape codes is required for this program to function as expected

## Installation

> A C++20 compatible compiler is required for this program to function as expected

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

A build configuration (`Debug`, `Release` etc.) can also be [specified](https://gist.github.com/Oakamoore/685838c1b4a4c64a008f5461ac9323b5).

#### Disabling Testing

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