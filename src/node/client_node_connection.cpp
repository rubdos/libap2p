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

#include "node/node_connection.hpp"
#include "node/client_node_connection.hpp"

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

namespace libap2p
{
/** Constructs a client connection to a specified ip:port.
 *  @param ip_adress    the ip_adress to connect to.
 *  @param port         the port to use for the connection
 */
client_node_connection::client_node_connection(std::string ip_adress, std::string port)
{
    boost::asio::io_service io_service;
    // Let's search the node...
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(ip_adress, port);
    // Set the iterator
    this->_endpoint_iterator = resolver.resolve(query);
}

/** Sends a message to this node_connection.
 *
 */
void client_node_connection::send_message(message* msg)
{
}
}
