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
#include "node/server_node_connection.hpp"
#include "message/message.hpp"
#include "message/header.hpp"

#include <boost/asio.hpp>

namespace libap2p
{
/** Creates a new node_connection based on a server sided socket.
 *  @param sock A socket pointer.
 */
server_node_connection::server_node_connection(boost::asio::ip::tcp::socket* sock)
{
    this->_socket = sock;
}

message* server_node_connection::fetch_message()
{
    header hdr;
    return NULL; //@todo: Implement
}

/** Sends a message to this node_connection.
 *
 */
void server_node_connection::send_message(message* msg)
{
    msg->prepare();
    header *hdr = msg->get_header();

    int64_t l_hdr = hdr->get_encoded();

    boost::system::error_code ignored_error;
    boost::asio::write(*(this->_socket), boost::asio::buffer(&l_hdr, 8), boost::asio::transfer_all(), ignored_error); // Send message header

    boost::asio::write(*(this->_socket), boost::asio::buffer(msg->get_encoded()), boost::asio::transfer_all(), ignored_error); // Send message itself
}

}
