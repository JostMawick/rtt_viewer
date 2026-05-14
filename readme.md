# RTT Viewer

A C++ application for reading and visualizing RTT (Real-Time Transfer) data from a Nordic nRF54L15 microcontroller via OpenOCD.

## Features

- Connects to OpenOCD control interface (TCP port 4444)
- Reads RTT data stream (TCP port 5555)
- Visualizes IMU data as text and 2D/3D graphs

## Requirements

- [CMake](https://cmake.org/) >= 3.21
- [Conan](https://conan.io/) 2.x (`pip install conan`)
- GCC via MSYS2 ucrt64 (`C:/msys64/ucrt64/bin/g++.exe`)
- MCU connected

## Setup

```bash
# Install dependencies (Debug)
conan install . --build=missing -s build_type=Debug

# Install dependencies (Release)
conan install . --build=missing -s build_type=Release
```

## Project Structure

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

## Dependencies

| Library | Version | Purpose           |
| ------- | ------- | ----------------- |
| fmt     | 12.1.0  | String formatting |

## Goals

- Readable Doxygen Output (just default settings rn)
