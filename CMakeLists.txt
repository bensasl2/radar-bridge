cmake_minimum_required(VERSION 3.12)
project(RadarBridge)


# Collect source files
set(BRIDGE_SOURCES
    RadarBridge.h     # not strictly needed in add_library, but can be listed
    RadarBridge.cpp
)

# Build as a shared library so we have exactly one instance of g_radarAPI
add_library(RadarBridge SHARED ${BRIDGE_SOURCES})

# Add the include directories so that dependents can include "RadarBridge.h"
target_include_directories(RadarBridge
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Let the compiler know we are building RadarBridge (dllexport) 
target_compile_definitions(RadarBridge PRIVATE BUILDING_RADAR_BRIDGE)
