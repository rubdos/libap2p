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

#include "libap2p/network/server.hpp"
#include "libap2p/network/network.hpp"

#include "iostream"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace libap2p
{
Server::Server()
{
}
/** Constructs a libap2p::server with specified network and port.
 *  @param nw   The libap2p::network object where the server will report to.
 *  @param cfg  The configuration details object.
 */
Server::Server(Network * nw, Configuration* cfg)
{
    this->_network = nw;
    this->_port = cfg->get<unsigned int>("server.port", 12011);
    this->_cfg = cfg;
}
/** Starts the server. Can be run in a separate thread.
 *  
 */
void Server::Run()
{
    for(;;)
    {
        tcp::acceptor acceptor(this->_io, tcp::endpoint(tcp::v4(), this->_port));
    
        tcp::socket * sock = new tcp::socket(this->_io);
    
        acceptor.accept(*sock);

        Node* nd = new Node(new ServerNodeConnection(sock));

        this->_network->AddNode(nd);
        this->onNodeConnect(nd);
    }
}
}
