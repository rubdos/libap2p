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

#ifndef CLASS_CLIENT_NODE_CONNECTION
#define CLASS_CLIENT_NODE_CONNECTION

#include "libap2p/node/node_connection.hpp"
#include "libap2p/message/message.hpp"

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/signals.hpp>

namespace libap2p
{
/** Implementation of connecting node_connection.
*
*/
class ClientNodeConnection : public NodeConnection
{
public:
    ClientNodeConnection(std::string /* IP address*/, std::string /* port */);
    void SendMessage(Message*);
    Message* FetchMessage();

    /** Connect using the ip/port combination from constructor
     */
    void Connect();
private:
    void _Connect();

    std::string _serverIpAdress;
    boost::asio::ip::tcp::resolver::iterator _endpointIterator;
    boost::asio::io_service _ioService;

    boost::thread *_connectorThread;
    boost::asio::ip::tcp::socket* _socket;
};
}

#endif
