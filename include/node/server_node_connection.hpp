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

#ifndef CLASS_SERVER_NODE_CONNECTION
#define CLASS_SERVER_NODE_CONNECTION

#include "node/node_connection.hpp"
#include "message/message.hpp"

#include <boost/asio.hpp>

namespace libap2p
{
/**
* @brief Implementation of listening node_connection.
*
*/
class server_node_connection : public node_connection
{
public:
	server_node_connection(boost::asio::ip::tcp::socket*);
	void send_message(message*);
private:
	boost::asio::ip::tcp::socket* _socket;
};
}

#endif
