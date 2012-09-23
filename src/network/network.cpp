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

#include "libap2p/network/server.hpp"
#include "libap2p/network/network.hpp"

namespace libap2p
{

/** Constructor. Initializes network structure
 *
 */
network::network(configuration* cfg)
{
    this->_cfg = cfg;
    this->_connection_status = DISCONNECTED;
    this->_local_identity = new identity();
    this->_local_identity->load_local();
}
/** Called to connect to the ap2p network. When called, ap2p connects to other
  * nodes specified with add_node() and fetches more from them. It will async
  * build up connections. The progress can be followed in network::status.
  * @warning An initial node is to be added with add_node or new network is created
  */
void network::connect()
{
    // Set status to connecting...
    this->_connection_status = CONNECTING;
    // Construct the libap2p::server object
    this->_server = new server(this, this->_cfg);
    this->_server->onNodeConnect.connect(boost::bind(&network::ServerNodeConnected, this, _1));
    if(this->_nodes.size() == 0)
    {
        // No nodes added, just start the server. Networks can be joined togheter later on.
        this->_connection_status = CONNECTED;
    }
    // Start the server in seperate thread
    this->_runner = new boost::thread(boost::bind(&libap2p::server::run, this->_server));
}

/** Function to close the network. Whenever the connection should be closed, 
  * this is to be called.
  */
void network::close()
{
    this->_connection_status = DISCONNECTED;
}
/** Add a node to the network. Called from the server or can be an initial node
 *  or one that's found on p2p manner in a client_node_connection way.
 *  @param _node    A libap2p::node object to add to the network.
 */
void network::add_node(node* _node)
{
    _node->onReceiveMessage.connect(boost::bind(&network::ReceivedMessage, this, _1, _2));
    _node->onConnected.connect(boost::bind(&network::NodeConnected, this, _1));
    this->onNodeAdded(_node);
    this->_nodes.push_back(_node);
}
void network::NodeConnected(node* nd)
{
    
}
void network::ReceivedMessage(message* msg, node* sender)
{
    switch (msg->GetMessageType())
    {
        case MESSAGE_HELLO:
            std::cout << "Received a hello message" << std::endl;
            break;
    }
    this->onReceiveMessage(msg, sender);
}
void network::ServerNodeConnected(node* nd)
{
    this->onNodeConnect(nd);
}
}
