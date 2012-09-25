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

#include <vector>

#include <boost/signals.hpp>

namespace libap2p
{
class server;
enum connection_status { CONNECTED, CONNECTING, DISCONNECTED, ERROR};


/** The main class which gives access to the whole network.
 * 
 */
class network
{
public:
    network(configuration*);
    void connect();
    void close();

    void add_node(node*);
/** Used to check the current connection status. Can be libap2p{connection_status
  * {CONNECTED, CONNECTING, DISCONNECTED or ERROR}};
  *
  */
    connection_status status() const {return this->_connection_status;};

    // Signals

    /** Signal that is called when a new node is added.
     *  
     */
    boost::signal<void (node*)> onNodeAdded;
    /** Signal called when a new node connects to the network
     */
    boost::signal<void (node*)> onNodeConnect;

    boost::signal<void (message*, node*)> onReceiveMessage;

    void ReceivedMessage(message*, node*);
    void ServerNodeConnected(node *);
    void NodeConnected(node *);

private:
    connection_status _connection_status;

    libap2p::server* _server;

    std::vector<node*> _nodes;
    Identity* _localIdentity;
    configuration* _cfg;
    boost::thread* _runner;
};
}
#endif
