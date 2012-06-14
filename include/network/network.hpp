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

#ifndef CLASS_NETWORK
#define CLASS_NETWORK

#include "node/node.hpp"

#include <vector>

namespace libap2p
{
enum connection_status { CONNECTED, CONNECTING, DISCONNECTED, ERROR};


/** The main class which gives access to the whole network.
* 
*/
class network
{
public:
	network();
	void connect();
	void close();

	void add_node(node*);
/** Used to check the current connection status. Can be libap2p{connection_status
  * {CONNECTED, CONNECTING, DISCONNECTED or ERROR}};
  *
  */
	connection_status status() const {return this->_connection_status;};
private:
	connection_status _connection_status;
};
}
#endif