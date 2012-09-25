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

#ifndef CLASS_NODE_CONNECTION
#define CLASS_NODE_CONNECTION

#include "libap2p/message/message.hpp"

#include <boost/signal.hpp>

namespace libap2p
{
/**  Abstract class providing the connection with a node. Implemented
  *  by server_node_connection or client_node_connection.
  */
class NodeConnection
{
public:
    /** Send a message object. 
	*/
	virtual void SendMessage(Message * ) = 0;
    virtual Message* FetchMessage() = 0;

    boost::signal<void ()> onConnected;

    bool connected;
};
}
#endif
