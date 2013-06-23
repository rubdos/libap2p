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

#ifndef CLASS_NETWORK
#define CLASS_NETWORK

#include "libap2p/identity/identity.hpp"
#include "libap2p/node/node.hpp"
#include "libap2p/configuration/configuration.hpp"
#include "libap2p/DHT/dht.hpp"
#include "libap2p/DHT/dht_entry.hpp"

#include <vector>

#include <boost/signals.hpp>

namespace libap2p
{
class Server;
enum connection_status { CONNECTED, CONNECTING, DISCONNECTED, ERROR};


/** The main class which gives access to the whole network.
 * 
 */
class Network
{
public:
    Network(Configuration*);
    Network(Configuration*, Identity* id);
    void Connect();
    void Close();

    void AddNode(Node*);
    /** Used to check the current connection status. Can be libap2p{connection_status
     * {CONNECTED, CONNECTING, DISCONNECTED or ERROR}};
     *
     */
    connection_status Status() const {return this->_connectionStatus;};

    // Signals

    /** Signal that is called when a new node is added.
     *  
     */
    boost::signal<void (Node*)> onNodeAdded;
    /** Signal called when a new node connects to the network
     */
    boost::signal<void (Node*)> onNodeConnect;

    boost::signal<void (Message*, Node*)> onReceiveMessage;

    /** Returns the nodes currently connected to.
     */
    NodeList GetNodes();

    /** Sends a message to the specified Node.
     */
    void SendMessage(Message* msg, Node* to);

private:
    void _OnNodeDisconnectHandler(Node* sender);
    void _OnNodeReceivedMessageHandler(Message*, Node*);
    void _OnServerNodeConnectedHandler(Node *);
    void _OnNodeConnectedHandler(Node *);

    connection_status _connectionStatus;

    libap2p::Server* _server;

    NodeList _nodes;
    Identity* _localIdentity;
    Configuration* _cfg;
    boost::thread* _runner;
    DHT* _dht;
};
}
#endif
