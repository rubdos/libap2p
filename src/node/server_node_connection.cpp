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

#include "libap2p/node/node_connection.hpp"
#include "libap2p/node/server_node_connection.hpp"
#include "libap2p/message/message.hpp"
#include "libap2p/message/header.hpp"

#include <boost/asio.hpp>
#include <stdio.h>
#include <vector>
#include <iostream>

namespace libap2p
{
/** Creates a new node_connection based on a server sided socket.
 *  @param sock A socket pointer.
 */
server_node_connection::server_node_connection(boost::asio::ip::tcp::socket* sock)
{
    this->_socket = sock;
    this->Connected = true;
}

message* server_node_connection::fetch_message()
{
    // Read header to determine message length. Header is 8 bytes long.
    int64_t *hdr_int = new int64_t();
    boost::asio::read(*(this->_socket), boost::asio::buffer(hdr_int, 8), boost::asio::transfer_at_least(8));
    
    header *hdr = new header(*hdr_int);
    
    // Prepare message retrieval
    boost::asio::streambuf message_raw; 

    size_t bytes = boost::asio::read( *(this->_socket), message_raw, boost::asio::transfer_at_least(hdr->message_length));
    
    // Make up message object and return
    return new message(&message_raw, hdr);
}

/** Sends a message to this node_connection.
 *
 */
void server_node_connection::send_message(message* msg)
{
    //@TODO: same code as in server connected. Should be abstracted in node.cpp 
    msg->prepare();
    
    header* hdr = msg->get_header();
    
    int64_t l_hdr = hdr->get_encoded();
    
    boost::system::error_code ignored_error;
    
    boost::asio::write(*(this->_socket), boost::asio::buffer(&l_hdr, 8), boost::asio::transfer_all(), ignored_error); // Send message header
    
    boost::asio::write(*(this->_socket), msg->get_encoded()->data(), boost::asio::transfer_all(), ignored_error); // Send message itself
}
}
