cmake_minimum_required (VERSION 2.6)
project (libap2p)
set(CMAKE_COLOR_MAKEFILE ON)
set(AP2P_LIBS node DHT)

include_directories ("${PROJECT_SOURCE_DIR}/include")
add_subdirectory(src)
