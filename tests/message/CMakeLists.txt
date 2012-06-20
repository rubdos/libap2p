add_executable(test_message message.cpp)
add_executable(test_message_header header.cpp)
target_link_libraries(test_message ap2p)
target_link_libraries(test_message_header ap2p)
