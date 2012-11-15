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
#include "libap2p/node/client_node_connection.hpp"

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/iostreams/copy.hpp>

namespace libap2p
{
/** Constructs a client connection to a specified ip:port.
 *  @param ip_adress    the ip_adress to connect to.
 *  @param port         the port to use for the connection
 */
ClientNodeConnection::ClientNodeConnection(std::string ip_adress, std::string port)
{
    // We didn't yet connect.
    this->connected = false;

    // Construct a socket using the io_service;
    this->_socket = new boost::asio::ip::tcp::socket(this->_ioService);
    // Let's search the node...
    boost::asio::ip::tcp::resolver resolver(this->_ioService);
    boost::asio::ip::tcp::resolver::query query(ip_adress, port, boost::asio::ip::tcp::resolver::query::all_matching);
    // Set the iterator by solving the ip_query
    this->_endpointIterator = resolver.resolve(query);
    // Connect

    this->_connectionString = ip_adress + ":" + port;
}

void ClientNodeConnection::Connect()
{
    this->_connectorThread = new boost::thread(&libap2p::ClientNodeConnection::_Connect, this); // Try connecting to the server
}

/** Tries to connect to the server specified in this->_endpoint_iterator.
 *  @note: internally called!
 *  @note: blocking, use on a separte thread!
 */
void ClientNodeConnection::_Connect()
{
    boost::asio::ip::tcp::resolver::iterator end;
    boost::system::error_code error = boost::asio::error::host_not_found;
    
    while(error && this->_endpointIterator != end)
    {
        this->_socket->close();
        this->_socket->connect(*(this->_endpointIterator++), error);
        if(error && error != boost::asio::error::host_not_found)
        {
            //@TODO: throw some error
        }
    }
    if(!error)
    {
        this->connected = true;
        this->onConnected();
    }
}

/** Sends a message to this node_connection.
 *
 */
void ClientNodeConnection::SendMessage(Message* msg)
{
    if(! this->connected) // Only send messages if we're connected
    {
        return;
    }
    //@TODO: same code as in server connected. Should be abstracted in node.cpp 
    msg->Prepare();
    
    Header* hdr = msg->GetHeader();
    
    int64_t l_hdr = hdr->GetEncoded();
    
    boost::system::error_code ignored_error;
    
    boost::asio::write(*(this->_socket), boost::asio::buffer(&l_hdr, 8), boost::asio::transfer_all(), ignored_error); // Send message header
    
    boost::asio::write(*(this->_socket), msg->GetEncoded()->data(), boost::asio::transfer_all(), ignored_error); // Send message itself
}
Message* ClientNodeConnection::FetchMessage()
{
    // No messages to read when not connected
    if(! this->connected )
    {
        return NULL;
    }

    // Prepare error catching
    boost::system::error_code error;

    // Read header to determine message length. Header is 8 bytes long.
    int64_t *hdr_int = new int64_t();
    boost::asio::read(
            *(this->_socket), 
            boost::asio::buffer(hdr_int, 8), 
            boost::asio::transfer_at_least(8), 
            error);

    if(error)
    {
        this->connected = false;
        return NULL;
    }
    
    Header *hdr = new Header(*hdr_int);
    
    // Prepare message retrieval
    boost::asio::streambuf message_raw;
    
    size_t bytes = boost::asio::read( 
            *(this->_socket), 
            message_raw, 
            boost::asio::transfer_at_least(hdr->messageLength),
            error);
    if(error)
    {
        this->connected = false;
        return NULL;
    }
    
    // Make up message object and return
    return new Message(&message_raw, hdr);
}
}
