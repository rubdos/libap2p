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
    // We didn't yet connect.
    this->connected = false;

    // First we need an io_service object...
    boost::asio::io_service io_service;
    // Construct a socket using the io_service;
    this->_socket = new boost::asio::ip::tcp::socket(io_service);
    // Let's search the node...
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(ip_adress, port);
    // Set the iterator by solving the ip_query
    this->_endpoint_iterator = resolver.resolve(query);
    // Connect
    this->_connector_thread = new boost::thread(&libap2p::client_node_connection::_connect, this); // Try connecting to the server
}


/** Tries to connect to the server specified in this->_endpoint_iterator.
 *  @note: internally called!
 *  @note: blocking, use on a separte thread!
 */
void client_node_connection::_connect()
{
    //boost::asio::connect(*(this->_socket), this->_endpoint_iterator);
    this->_socket->connect(*(this->_endpoint_iterator)); //@FIXME: Will cause null pointer errors!
    this->connected = true;
}

/** Sends a message to this node_connection.
 *
 */
void client_node_connection::send_message(message* msg)
{
    if(this->connected) // Only send messages if we're connected
    {
        //@TODO: same code as in server connected. Should be abstracted in node.cpp 
        msg->prepare();
        header *hdr = msg->get_header();

        int64_t l_hdr = hdr->get_encoded();

        boost::system::error_code ignored_error;
        boost::asio::write(*(this->_socket), boost::asio::buffer(&l_hdr, 8), boost::asio::transfer_all(), ignored_error); // Send message header

        boost::asio::write(*(this->_socket), boost::asio::buffer(msg->get_encoded()), boost::asio::transfer_all(), ignored_error); // Send message itself
    }
}
}
