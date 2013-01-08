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
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

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
    this->_server->onNodeConnect.connect(
            boost::bind(
                &Network::_OnServerNodeConnectedHandler, 
                this, 
                _1)
            );

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
    _node->onReceiveMessage.connect(
            boost::bind(
                &Network::_OnNodeReceivedMessageHandler, 
                this, 
                _1, 
                _2)
            );
    _node->onConnected.connect(
            boost::bind(
                &Network::_OnNodeConnectedHandler, 
                this, 
                _1)
            );
    _node->onDisconnected.connect(
            boost::bind(
                &Network::_OnNodeDisconnectHandler, 
                this, 
                _1)
            );
    this->onNodeAdded(_node);
    this->_nodes.push_back(_node);
}
NodeList Network::GetNodes()
{
    return this->_nodes;
}
void Network::_OnNodeConnectedHandler(Node* nd)
{    
    std::stringstream id_params;
    id_params << this->_localIdentity->GetPublicKey();
    Message* init_msg = new Message(MESSAGE_HELLO, id_params.str());
    init_msg->Sign(this->_localIdentity);
    nd->SendMessage(init_msg);
}
void Network::SendMessage(Message* msg, Node* to)
{
    msg->Sign(this->_localIdentity);
    to->SendMessage(msg);
}
void Network::_OnNodeReceivedMessageHandler(Message* msg, Node* sender)
{
    switch (msg->GetMessageType())
    {
        case MESSAGE_HELLO:
            {
                // Check for double connections!

                for(NodeList::iterator nit = this->_nodes.begin();
                        nit != this->_nodes.end();
                        ++nit)
                {
                    if(
                            (*nit) != sender // Different connection
                            && // But
                            (*nit)->GetFingerprint().compare(sender->GetFingerprint()) == 0 // Same node
                            )
                    {
                        sender->Disconnect();
                    }
                }

                // Check for loopback connections!
                if(this->_localIdentity->GetFingerprint().compare(sender->GetFingerprint()) == 0)
                {
                    // Houston, we've got a problem. Delete the node, it's ourself
                    sender->Disconnect();
                    break;
                }

                // Ask for more info on the node
                Message* info_req = new Message(MESSAGE_NODE_INFO_REQUEST, "");
                info_req->Sign(this->_localIdentity);
                sender->SendMessage(info_req);
                break;
            }
        case MESSAGE_NODE_INFO_REQUEST:
            {
                boost::property_tree::ptree pt; // Where to store the node-info
                std::stringstream response; 

                std::string port = this->_cfg->get<std::string>("server.port", "12011");

                pt.put("listenport", port);
                write_xml(response, pt);

                Message* info_ans = new Message(MESSAGE_NODE_INFO_RESPONSE, response.str());
                info_ans->Sign(this->_localIdentity);
                sender->SendMessage(info_ans);
                break;
            }
        case MESSAGE_NODE_INFO_RESPONSE:
            {
                // Ask for other nodes
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
                typedef std::vector<std::string> splitvec_t;
                splitvec_t nodes_r;
                boost::algorithm::split(nodes_r,
                        data,
                        boost::algorithm::is_any_of("\n\r"),
                        boost::algorithm::token_compress_on);
                
                for(splitvec_t::iterator n_it = nodes_r.begin();
                        n_it != nodes_r.end();
                        ++n_it)
                {
                    /*
                       Fields are declared as follows:
                       0 -> ip:host
                       1 -> sha256sum of the public key
                       And splitted by \t or a space character
                       */
                    splitvec_t fields;
                    boost::algorithm::split(fields,
                            *n_it,
                            boost::algorithm::is_any_of(" \t"),
                            boost::algorithm::token_compress_on);
                    if(fields.size() >= 2)
                    {
                        // We have a legit field
                        std::string host_port   = fields[0];
                        std::string sha256      = fields[1]; //TODO Check this sum?

                        // Split the host from the port and add a node to the network.
                        splitvec_t host_port_arr;
                        boost::algorithm::split(host_port_arr,
                                host_port,
                                boost::algorithm::is_any_of(":"),
                                boost::algorithm::token_compress_on);

                        if(host_port_arr.size() != 2)
                        {
                            //TODO Throw an error?
                        }
                        else
                        {
                            // First check if we don't already have this node.
                            bool found = false;
                            for(NodeList::iterator known = this->_nodes.begin();
                                    known != this->_nodes.end();
                                    ++known)
                            {
                                if((*known)->GetFingerprint().compare(sha256) == 0)
                                {
                                    found = true;
                                }
                            }
                            if(!found)
                            {
                                // We found a node in our network! Let's add it!
                                Node* n;
                                ClientNodeConnection* cnc;
                                cnc = new ClientNodeConnection(host_port_arr[0], host_port_arr[1]);
                                n = new Node(cnc);
                                cnc->Connect();
                                this->AddNode(n);
                            }
                        }
                    }
                    else
                    {
                        //@TODO Throw an error!!!
                    }
                }
                break;
            }
        case MESSAGE_DHT_SEARCH:
            {
                // Construct a DHT_SEARCH_RESULT
                break;
            }
        case MESSAGE_DHT_INFO:
            {
                // Construct a DHT_INFO_RESULT
                break;
            }
        case MESSAGE_DHT_FETCH:
            {
                // Construct a DHT_PUSH
                std::cout << "Received a FETCH request:" << std::endl;

                std::string data = msg->GetData();
                std::cout << data << std::endl;

                //Message* msg = new Message(MESSAGE_DHT_PUSH, "<sha>" + "</sha>");
                break;
            }
        case MESSAGE_DHT_SEARCH_RESULT:
            {
                // Received a list of DHTEntry objects.
                break;
            }
        case MESSAGE_DHT_INFO_RESULT:
            {
                // Received a DHT info request
                break;
            }
        case MESSAGE_DHT_PUSH:
            {
                // Received a DHT object
                break;
            }
        default:
            this->onReceiveMessage(msg, sender);
            break;
    }
}
void Network::_OnNodeDisconnectHandler(Node* sender)
{
    // delete and remove the node
    for(NodeList::iterator nit = this->_nodes.begin();
            nit != this->_nodes.end();
            nit++)
    {
        if(*nit == sender)
        {
            this->_nodes.erase(nit);
            break;
        }
    }
    delete sender;
}
void Network::_OnServerNodeConnectedHandler(Node* nd)
{
    this->_OnNodeConnectedHandler(nd);
    this->onNodeConnect(nd);
}
}
