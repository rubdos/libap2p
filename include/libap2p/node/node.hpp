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

#include "libap2p/node/node_connection.hpp"
#include "libap2p/node/server_node_connection.hpp"
#include "libap2p/node/client_node_connection.hpp"
#include "libap2p/message/message.hpp"
#include "libap2p/identity/identity.hpp"

#include <stdlib.h>
#include <iostream>
#include <queue>

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/signals.hpp>

namespace libap2p
{
/**
* @brief:Represents a peer in the libap2p::network.
* Used to send libap2p::message
* objects, receiving them and other communication.
*/
class Node
{
public:
    Node();
    Node(NodeConnection*);

    /** Default destructor.
     *
     */
    ~Node();

    void SendMessage(Message*);
    /** Returns the connectionstring in host:port format.
     *
     */
    std::string GetConnectionString();
    std::string GetFingerprint();

    void Run();
    void _Run();

    boost::signal<void (Message*, Node* /* sender */)> onReceiveMessage;
    boost::signal<void (Node* /* sender */)> onConnected;
    boost::signal<void (Node* /* sender */)> onDisconnected;

    void Connected();
private:    
    NodeConnection* _nodeConnection;

    boost::thread* _runner;

    Identity _id;
    std::queue<Message*> _sendQueue;
    bool _queueRunning;
};
typedef std::vector<Node*> NodeList;
}
#endif
