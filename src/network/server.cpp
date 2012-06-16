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

#include "network/server.hpp"
#include "network/network.hpp"

#include "iostream"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace libap2p
{
server::server()
{
}
/** Constructs a libap2p::server with specified network and port.
 *  @param nw   The libap2p::network object where the server will report to.
 *  @param port The uint TCP port where the server will listen on.
 */
server::server(network * nw, unsigned short port)
{
    this->_network = nw;
    this->_port = port;
}
/** Starts the server. Can be run in a separate thread.
 *  
 */
void server::run()
{
    for(;;)
    {
        tcp::acceptor acceptor(this->io, tcp::endpoint(tcp::v4(), this->_port));
    
        tcp::socket * sock = new tcp::socket(this->io);
    
        acceptor.accept(*sock);

        this->_network->add_node(new node(new server_node_connection(sock)));
    }
}
}
