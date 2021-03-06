# - Basic CMake setup
# Check version meets ou requirements
# Declare project, which will configure compiler for us
cmake_minimum_required(VERSION 2.8)
project(TestCalorimeterCalibration)

# # Modules use Bayeux, so we need to locate this or fail
# find_package(Bayeux REQUIRED)

# Modules use Falaise, so we need to locate this or fail
find_package(Falaise REQUIRED)

# Ensure our code can see the Bayeux headers
include_directories(${Falaise_INCLUDE_DIRS})

# Build a dynamic library from our sources
add_library(TestCalorimeterCalibration SHARED
  test_calorimeter_s2c_module.h
  test_calorimeter_s2c_module.cc
  )

# Install libraries
install(FILES
  ${PROJECT_BINARY_DIR}/libTestCalorimeterCalibration${CMAKE_SHARED_LIBRARY_SUFFIX}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  PERMISSIONS OWNER_READ OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  )
