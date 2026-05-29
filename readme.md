# RTT Viewer

A C++ application for reading and visualizing RTT (Real-Time Transfer) data from a Nordic nRF54L15 microcontroller via OpenOCD.
But for the university version of this project the data will be simulated and the visualization will happen in the terminal.

Note:
For now this will be just a student project. It will not include any third-party libraries. It can be compiled with g++. The instructions to compile and execute can be found below. The additional files like CMakeLists.txt or conanfile.txt can be ignored for this project. But since the project should be used later with libraries, the existing files will remain. They do not affect the working of the university version.

## Features

- Generates IMU-Data (Sinus curves or other Movements)
- Generates noise over the IMU-Data with math.random()
- Filters the nosie with Kalmann-Filter
- Calculates Quanterionen based on the 6 Achses IMU
- Visualizes IMU data as text and terminal graphs (ASII-Codes)

## Compile and execute

```bash
# Compile
g++ -std=c++14 src/main.cpp -o rtt_viewer.exe

# Execute
.\rtt_viewer.exe
```

## Requirements (only for future versions)

- [CMake](https://cmake.org/) >= 3.21
- [Conan](https://conan.io/) 2.x (`pip install conan`)
- [Doxygen](https://www.doxygen.nl/)
- GCC via MSYS2 ucrt64
- MCU connected

## Setup (only for future versions)

```bash
# Install dependencies (Debug)
conan install . --build=missing -s build_type=Debug

# Install dependencies (Release)
conan install . --build=missing -s build_type=Release
```

## Project Structure (/out, /build, /conanfile.txt, /CMakefile.txt are ignored)

```
rtt_viewer/
├── src/          # Source files (.cpp)
├── include/      # Header files (.h)
├── build/        # Conan generated files
├── out/          # CMake build output
├── tests/        # testing (optional)
├── CMakeLists.txt
└── conanfile.txt
```

## Dependencies (No dependencys for univerity project)

## Goals

- Get a good grade
- Readable Doxygen Output (just default settings rn)
- Switch from random Numbers to the actual data stream of the MCU
- Switch from Terminal Graphs to proper 2D and 3D graphs
