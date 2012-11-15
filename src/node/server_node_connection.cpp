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
ServerNodeConnection::ServerNodeConnection(boost::asio::ip::tcp::socket* sock)
{
    this->_socket = sock;
    this->connected = true;
}

Message* ServerNodeConnection::FetchMessage()
{
    // Read header to determine message length. Header is 8 bytes long.
    int64_t *hdr_int = new int64_t();
    boost::asio::read(*(this->_socket), boost::asio::buffer(hdr_int, 8), boost::asio::transfer_at_least(8));
    
    Header *hdr = new Header(*hdr_int);
    
    // Prepare message retrieval
    boost::asio::streambuf message_raw; 

    size_t bytes = boost::asio::read(
            *(this->_socket), 
            message_raw, 
            boost::asio::transfer_at_least(hdr->messageLength)
            );
    
    // Make up message object and return
    return new Message(&message_raw, hdr);
}

/** Sends a message to this node_connection.
 *
 */
void ServerNodeConnection::SendMessage(Message* msg)
{
    //@TODO: same code as in server connected. Should be abstracted in node.cpp 
    msg->Prepare();
    
    Header* hdr = msg->GetHeader();
    
    int64_t l_hdr = hdr->GetEncoded();
    
    boost::system::error_code ignored_error;
    
    boost::asio::write(
            *(this->_socket), 
            boost::asio::buffer(&l_hdr, 8), 
            boost::asio::transfer_all(), ignored_error); // Send message header
    
    if(ignored_error)
    {
        std::cout << "Error sending header" << std::endl;
    }

    boost::asio::write(
            *(this->_socket),
            msg->GetEncoded()->data(), 
            boost::asio::transfer_all(), ignored_error); // Send message itself

    if(ignored_error)
    {
        std::cout << "Error sending message" << std::endl;
    }
}
}
