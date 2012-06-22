add_executable(test_create_network create_network.cpp)
target_link_libraries(test_create_network ap2p)

add_executable(test_connect connect.cpp)
target_link_libraries(test_connect ap2p)
