/* Copyright (C) 
* 2012 - Ruben De Smet
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3
* of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://gnu.org/licenses/>
* 
*/

#ifndef CLASS_NODE
#define CLASS_NODE

#include "node/node_connection.hpp"
#include "node/server_node_connection.hpp"
#include "node/client_node_connection.hpp"
#include "message/message.hpp"

#include <stdlib.h>
#include <iostream>

namespace libap2p
{
/**
* @brief:Represents a peer in the libap2p::network.
* Used to send libap2p::message
* objects, receiving them and other communication.
*/
class node
{
public:
    node();
    node(node_connection*);
    bool connect();
    void send_message(message*);

    void run();
private:
    void _run();
    
    node_connection *_node_connection;
};
}
#endif
