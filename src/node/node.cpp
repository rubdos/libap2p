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

#include "node/node.hpp"
#include "node/node_connection.hpp"

namespace libap2p
{
/* Constructor, initializes a node object.
 *
 */
node::node()
{
    this->_node_connection = NULL;
}
/** Constructs a new node with a known connection.
 *  @param nc   A node connection.
 */
node::node(node_connection* nc)
{
    this->_node_connection = nc;
}

/** Runs the node connections.
 *  Will start separate thread.
 */
void node::run()
{
    message* init_msg = new message(MESSAGE_IDENTIFY, ""); //@todo: add identification params (pubid)
    this->send_message(init_msg);

    this->runner = new boost::thread(boost::bind(&libap2p::node::_run, this)); 
}
/** Actual runner.
 *  Runs in thread started by node::run();
 */
void node::_run()
{
    while(true)
    {
        if(this->_node_connection == NULL)
        {
            break;
        }
        message* msg = this->_node_connection->fetch_message();
        if(msg == NULL)
        {
            break;
        }
        // std::cout << msg->get_xml() << std::endl;
    }
}

/** Send a libap2p::message object to another node.
 *  @param msg  A message object to be send
 */
void node::send_message(message* msg)
{
    this->_node_connection->send_message(msg); // Well, this is simple...
}
}
