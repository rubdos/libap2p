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


#include "network/network.hpp"

namespace libap2p
{

/** Constructor. Initializes network structure
 *
 */
network::network()
{
	this->_connection_status = DISCONNECTED;
}
/** Called to connect to the ap2p network. When called, ap2p connects to other
  * nodes specified with add_node() and fetches more from them. It will async
  * build up connections. The progress can be followed in network::status.
  * @warning An initial node is to be added with add_node or new network is created
  */
void network::connect()
{
	this->_connection_status = CONNECTING;
}

}
