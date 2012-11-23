add_executable(test_dht dht.cpp)
target_link_libraries(test_dht ap2p ${AP2P_LIBS} ${Boost_LIBRARIES} ${CRYPTOPP_LIBRARIES})
