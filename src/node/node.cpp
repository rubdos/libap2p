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
#include "node/node.hpp"
namespace libap2p
{
/**
* @brief: Constructor. Initializes node object
*
*/
node::node()
{
	this->_node_connection = NULL;
}

bool node::connect()
{
	//!\todo: insert connection stuff here.
	return false; //stub
}

/**
* @brief: Send a libap2p::message object to another node
* @throws: 
*/
void node::send_message(message* msg)
{
	if(this->connect())
	{
		
	}
	
}
}
