set(AP2P_SRC ap2p.cpp)
add_library(libap2p SHARED ${AP2P_SRC})
install (TARGETS libap2p LIBRARY DESTINATION lib))
