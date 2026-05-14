cmake_minimum_required(VERSION 3.10.0)
project(rtt_viewer VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt REQUIRED)

add_executable(rtt_viewer 
src/main.cpp)

target_link_libraries(rtt_viewer PRIVATE fmt::fmt)
