cmake_minimum_required(VERSION 3.10)
project(pm3)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add library
add_library(pm3lib pm3/pm3.cc)

# Include directories for the library
target_include_directories(pm3lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pm3)

# Create executable
add_executable(pm3 main.cc)

# Link the library with the executable
target_link_libraries(pm3 PRIVATE pm3lib)
