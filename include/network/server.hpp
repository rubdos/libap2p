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

#include "configuration/configuration.hpp"
#include "node/node.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/signals.hpp>

namespace libap2p
{
class network;
/** Main p2p listening class.
 *  Internally called.
 */
class server
{
public:
    server();
    server(libap2p::network*, configuration* cfg);
    void run();

    boost::signal<void (node*)> onNodeConnect;
private:
    void handle_accept(boost::asio::ip::tcp::socket, const boost::system::error_code&);
    
    boost::asio::io_service io;
    unsigned short _port;

    network* _network;
    configuration* _cfg;
};
}
#endif
