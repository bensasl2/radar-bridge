cmake_minimum_required(VERSION 3.12)
project(RadarBridge LANGUAGES CXX)

# Build as a shared library so we have exactly one instance of g_radarAPI
add_library(RadarBridge SHARED
    RadarBridge.cpp
    # Add more .cpp files if needed
)

# Let the compiler know we are building RadarBridge (dllexport) 
target_compile_definitions(RadarBridge PRIVATE BUILDING_RADAR_BRIDGE)

# If you'd like a specific C++ standard, do:
set_target_properties(RadarBridge PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
)

# Possibly set version information
set_target_properties(RadarBridge PROPERTIES
  SOVERSION 1
  VERSION 1.0.0
)

# That's all. We do not link or find wxWidgets here. 
