add_executable(test_conf configuration.cpp)
target_link_libraries(test_conf ap2p ${Boost_LIBRARIES})

file(COPY configuration.xml DESTINATION ${PROJECT_BINARY_DIR})
