# Shamir's Secret Sharing Algorithm - C++ Implementation

This repository contains a C++ implementation of a simplified version of Shamir's Secret Sharing algorithm. The program reads polynomial data from a JSON file, decodes it, performs Lagrange interpolation, and computes the constant term \( c \) of the polynomial.

## Prerequisites

1. **C++ Compiler**: Ensure you have a C++ compiler installed (e.g., `g++` for GCC).

2. **nlohmann/json Library**: This code uses the `nlohmann/json` library for JSON parsing. You can either download the header file or use a package manager to install it.

## Installation

### Option 1: Direct Download of nlohmann/json

1. Download the `json.hpp` file from the [nlohmann/json GitHub repository](https://github.com/nlohmann/json).
2. Place the `json.hpp` file in the same directory as your C++ code.

### Option 2: Using a Package Manager

- **vcpkg**:
  1. Install vcpkg following the instructions [here](https://github.com/microsoft/vcpkg).
  2. Run `vcpkg install nlohmann-json` to install the library.

- **Conan**:
  1. Install Conan following the instructions [here](https://conan.io/downloads.html).
  2. Create a `conanfile.txt` with the following content:
     ```
     [requires]
     nlohmann_json/3.11.2
     
     [generators]
     cmake
     ```
  3. Run `conan install .` to install the library.

## Files

- `shamir.cpp`: C++ source code for reading JSON, decoding values, and computing the polynomial constant term.
- `input.json`: Example JSON file containing polynomial data (you should create this file based on your test case).

## Usage

1. **Save the C++ code**:
   - Save the provided C++ code into a file named `shamir.cpp`.

2. **Create the JSON Input File**:
   - Create a file named `input.json` with your polynomial data in JSON format. Ensure it is in the same directory as `shamir.cpp`.

3. **Compile the Code**:

   ```sh
   g++ -o shamir shamir.cpp -I/path/to/json/include
