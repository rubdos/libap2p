cmake_minimum_required (VERSION 2.6)
project (libap2p)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")
set(CMAKE_COLOR_MAKEFILE ON)
set(AP2P_LIBS identity node node_connection DHT message configuration)
set(INCLUDE_FILES
    include/libap2p/identity/identity.hpp
    include/libap2p/network/network.hpp
    include/libap2p/network/server.hpp
    include/libap2p/DHT/dht_entry.hpp
    include/libap2p/DHT/dht.hpp
    include/libap2p/configuration/configuration.hpp
    include/libap2p/message/header.hpp
    include/libap2p/message/message.hpp
    include/libap2p/node/server_node_connection.hpp
    include/libap2p/node/node_connection.hpp
    include/libap2p/node/client_node_connection.hpp
    include/libap2p/node/node.hpp
)


# ---------- Setup output Directories -------------------------
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/bin
   CACHE PATH
   "Single Directory for all Libraries"
   )

# --------- Setup the Executable output Directory -------------
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/bin
   CACHE PATH
   "Single Directory for all Executables."
   )

# --------- Setup the Executable output Directory -------------
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/bin
   CACHE PATH
   "Single Directory for all static libraries."
   )

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON) 
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS iostreams filesystem system thread signals)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif(Boost_FOUND)

find_package (Threads REQUIRED)
find_package (CryptoPP REQUIRED)
find_package (Readline) #not required

include_directories ("${PROJECT_SOURCE_DIR}/include")
include_directories ("${CRYPTOPP_INCLUDE_DIRS}")
add_subdirectory(src)
add_subdirectory(tests)

# INSTALL

foreach(file ${INCLUDE_FILES})
    string(REGEX MATCH "(.*)[/\\]" DIR ${file})
    install(FILES ${file} DESTINATION ${DIR})
endforeach()

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  SET_TARGET_PROPERTIES(${AP2P_LIBS} PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
