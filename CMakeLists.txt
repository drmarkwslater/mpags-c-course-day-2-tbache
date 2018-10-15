# Main CMake buildscript for mpags-cipher

# Set CMake requirements then decalre project
cmake_minimum_required(VERSION 3.2)
project(MPAGSCipher VERSION 0.1.0)

# When Makefiles are generated, output all command lines by default
# Do this to begin with so it's easy to see what compiler command/flags are used. This can also be done by removing the set command and running make as 'make VERBOSE=1'.
set(CMAKE_VERBOSE_MAKEFILE ON)

# Set the C++ Standard directly
set(CMAKE_CXX_STANDARD 11)

# Declare the build of mpags-cipher main program
add_executable(mpags-cipher
  mpags-cipher.cpp
  MPAGSCipher/TransformChar.cpp
  MPAGSCipher/TransformChar.hpp
  )

# Set where CMake searches for header files
target_include_directories(mpags-cipher
  PRIVATE MPAGSCipher
  )

# Don't allow C++ compiler vendor extensions
set(CMAKE_CXX_EXTENSIONS OFF)

# Use our standard set of flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic")

# Declare the compile features
target_compile_features(mpags-cipher
  PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization
  )

