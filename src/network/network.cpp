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

#include <string>
#include <sstream>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

namespace libap2p
{

/** Constructor. Initializes network structure
 *
 */
Network::Network(Configuration* cfg)
{
    this->_cfg = cfg;
    this->_connectionStatus = DISCONNECTED;
    this->_localIdentity = new Identity();
    this->_localIdentity->LoadLocal();
}
/** Constructor. Initializes network structure.
 *
 */
Network::Network(Configuration* cfg, Identity* id)
{
    this->_cfg = cfg;
    this->_connectionStatus = DISCONNECTED;
    this->_localIdentity = id;
}
/** Called to connect to the ap2p network. When called, ap2p connects to other
  * nodes specified with add_node() and fetches more from them. It will async
  * build up connections. The progress can be followed in network::status.
  * @warning An initial node is to be added with add_node or new network is created
  */
void Network::Connect()
{
    // Set status to connecting...
    this->_connectionStatus = CONNECTING;
    // Construct the libap2p::server object
    this->_server = new Server(this, this->_cfg);
    this->_server->onNodeConnect.connect(boost::bind(&Network::ServerNodeConnected, this, _1));
    if(this->_nodes.size() == 0)
    {
        // No nodes added, just start the server. Networks can be joined togheter later on.
        this->_connectionStatus = CONNECTED;
    }
    // Start the server in seperate thread
    this->_runner = new boost::thread(boost::bind(&Server::Run, this->_server));
}

/** Function to close the network. Whenever the connection should be closed, 
  * this is to be called.
  */
void Network::Close()
{
    this->_connectionStatus = DISCONNECTED;
}
/** Add a node to the network. Called from the server or can be an initial node
 *  or one that's found on p2p manner in a client_node_connection way.
 *  @param _node    A libap2p::node object to add to the network.
 */
void Network::AddNode(Node* _node)
{
    _node->onReceiveMessage.connect(boost::bind(&Network::ReceivedMessage, this, _1, _2));
    _node->onConnected.connect(boost::bind(&Network::NodeConnected, this, _1));
    this->onNodeAdded(_node);
    this->_nodes.push_back(_node);
}
NodeList Network::GetNodes()
{
    return this->_nodes;
}
void Network::NodeConnected(Node* nd)
{    
    std::stringstream id_params;
    id_params << this->_localIdentity->GetPublicKey();
    Message* init_msg = new Message(MESSAGE_HELLO, id_params.str());
    init_msg->Sign(this->_localIdentity);
    nd->SendMessage(init_msg);
}
void Network::ReceivedMessage(Message* msg, Node* sender)
{
    switch (msg->GetMessageType())
    {
        case MESSAGE_HELLO:
            {
                // Ask for nodes
                Message* discovery_msg = new Message(MESSAGE_NODES_REQUEST, "");
                discovery_msg->Sign(this->_localIdentity);
                sender->SendMessage(discovery_msg);
                break;
            }
        case MESSAGE_NODES_REQUEST:
            {
                // Make node list.
                std::stringstream nodes;
                for(std::vector<Node*>::iterator nit = this->_nodes.begin();
                        nit != this->_nodes.end();
                        nit++)
                {
                    if((*nit) != sender) // Don't return the sender. Would be stupid, right?
                    {
                        nodes << (*nit)->GetConnectionString() << " " << (*nit)->GetFingerprint() << std::endl;
                    }
                }
                // Now send the message
                Message* nd_resp = new Message(MESSAGE_NODES_RESPONSE, nodes.str());
                nd_resp->Sign(this->_localIdentity);
                sender->SendMessage(nd_resp);
                break;
            }
        case MESSAGE_NODES_RESPONSE:
            {
                // Received a list of nodes. Try to connect to each one of them.
                std::string data = msg->GetData();
                std::vector<std::string> nodes_response;
                boost::algorithm::split(nodes_response,
                        data,
                        boost::algorithm::is_any_of("\n\r"),
                        boost::algorithm::token_compress_on);
                break;
            }
        default:
            this->onReceiveMessage(msg, sender);
            break;
    }
}
void Network::ServerNodeConnected(Node* nd)
{
    this->NodeConnected(nd);
    this->onNodeConnect(nd);
}
}
