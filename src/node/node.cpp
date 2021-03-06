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

#include "libap2p/node/node.hpp"
#include "libap2p/node/node_connection.hpp"

namespace libap2p
{
/* Constructor, initializes a node object.
 *
 */
Node::Node()
{
    this->_nodeConnection = NULL;
    this->_queueRunning = false;
}
/** Constructs a new node with a known connection.
 *  @param nc   A node connection.
 */
Node::Node(NodeConnection* nc)
{
    this->_nodeConnection = nc;
    this->_queueRunning = false;
    if(!nc->connected)
    {
        nc->onConnected.connect(boost::bind(&Node::Connected, this));
    }
    else
    {
        this->Connected();
    }
}

std::string Node::GetIp()
{
    return this->_nodeConnection->GetIp();
}

/** Runs the node connections.
 *  Will start separate thread.
 */
void Node::Run()
{
    this->_runner = new boost::thread(boost::bind(&libap2p::Node::_Run, this)); 
}
/** Actual runner.
 *  Runs in thread started by node::run();
 */
void Node::_Run()
{
    while(true)
    {
        if(this->_nodeConnection == NULL)
        {
            this->onDisconnected(this);
            break;
        }
        Message* msg = this->_nodeConnection->FetchMessage();
        if(msg == NULL)
        {
            // Disconnect node for now. @TODO: Try a reconnection.
            this->onDisconnected(this);
            break;
        }
        // Received a message

        switch(msg->GetMessageType())
        {
            case MESSAGE_HELLO:
                {
                    try
                    {
                        this->_id.LoadPublicKey(msg->GetData());
                    }
                    catch(...)
                    {
                        // Node data was probably messed up. @TODO: Catch this stuff!
                    }
                    break;
                }
            case MESSAGE_NODE_INFO_RESPONSE:
                {
                    boost::property_tree::ptree pt;
                    std::stringstream in;

                    in << msg->GetData();
                    read_xml(in, pt);

                    std::string listenport = pt.get<std::string>("listenport", "12011");

                    this->_nodeConnection->SetConnectionString(this->GetIp() + ":" + listenport);

                    break;
                }
        }
        this->onReceiveMessage(msg, this /* sender */);
    }
}

/** Send a libap2p::message object to another node.
 *  @param msg  A message object to be send
 */
void Node::SendMessage(Message* msg)
{
    this->_sendQueue.push(msg);
    
    if(! this->_queueRunning)
    {
        this->_queueRunning = true;
        while(!this->_sendQueue.empty())
        {
            this->_nodeConnection->SendMessage(this->_sendQueue.front()); // Well, this is simple...
            this->_sendQueue.pop();
        }
        this->_queueRunning = false;
    }
}

std::string Node::GetFingerprint()
{
    return this->_id.GetFingerprint();
}

std::string Node::GetConnectionString()
{
    return this->_nodeConnection->GetConnectionString();
}

void Node::Connected()
{
    this->Run();
    
    this->onConnected(this /* Sender */ );
}

void Node::Disconnect()
{
    this->onDisconnected(this);
}

Node::~Node()
{
    delete this->_nodeConnection;
    delete this->_runner;
    // Runner thread will end and destruct automatically, no need to destroy
}
}
