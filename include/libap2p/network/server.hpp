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

#ifndef CLASS_LIBAP2P_SERVER
#define CLASS_LIBAP2P_SERVER

#include "libap2p/configuration/configuration.hpp"
#include "libap2p/node/node.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/signals.hpp>

namespace libap2p
{
class Network;
/** Main p2p listening class.
 *  Internally called.
 */
class Server
{
public:
    Server();
    Server(libap2p::Network*, Configuration* cfg);
    void Run();

    boost::signal<void (Node*)> onNodeConnect;
private:
    void _HandleAccept(boost::asio::ip::tcp::socket, const boost::system::error_code&);
    
    boost::asio::io_service _io;
    unsigned short _port;

    Network* _network;
    Configuration* _cfg;
};
}
#endif
