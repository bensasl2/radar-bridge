cmake_minimum_required(VERSION 3.12)
project(RadarBridge)


# Collect source files
set(BRIDGE_SOURCES
    RadarBridge.h     # not strictly needed in add_library, but can be listed
    RadarBridge.cpp
)

# Build as a shared library so we have exactly one instance of g_radarAPI
add_library(RadarBridge SHARED ${BRIDGE_SOURCES})



# Let the compiler know we are building RadarBridge (dllexport) 
target_compile_definitions(RadarBridge PRIVATE BUILDING_RADAR_BRIDGE)
