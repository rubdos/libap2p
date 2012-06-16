set(NODE_SRC node.cpp)
add_library(node ${NODE_SRC})

set(NODE_CONNECTION_SRC client_node_connection.cpp server_node_connection.cpp)
add_library(node_connection ${NODE_CONNECTION_SRC})
