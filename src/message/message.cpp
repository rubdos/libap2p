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

#include "message/message.hpp"

namespace libap2p
{

/**
* @brief Default constructor
*/
message::message()
{
}

/**
* @brief Constructor with data
* Used to prepare a message to be send 
* @param messagetype 	Message type. Can be any uint. Will be send through the socket
* @param data		The data to send. Easy construction by boost::asio::buffer([anything here]);
*/
message::message(unsigned int messagetype, std::string data)
{
	this->_message_type = messagetype;
	this->_data = data;
}

std::string message::get_xml()
{
	/** @todo Stub, to complete! */
	return "";
}
}
