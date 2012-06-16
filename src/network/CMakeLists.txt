set(NETWORK_SRC network.cpp server.cpp)
add_library(ap2p SHARED ${NETWORK_SRC})
target_link_libraries(ap2p ${AP2P_LIBS} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install (TARGETS ap2p LIBRARY DESTINATION lib)
