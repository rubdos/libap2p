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

#define MESSAGETESTTYPE 123

#include "message/message.hpp"
#include "iostream"

int main()
{
    // Create a new message
    libap2p::message* msg = new libap2p::message(MESSAGETESTTYPE, "Test content<as>you see, xml content can be set as data!</as>");
    // Print the XML data constructed in the message
    std::cout << "XML:" << std::endl << msg->get_xml() << std::endl << std::endl;

    // Construct a new message from the XML data
    std::cout << "Constructing new message from XML:" << std::endl;
    libap2p::message* from_xml = new libap2p::message(msg->get_xml());
    // And print the new message to the terminal
    std::cout << from_xml->get_xml() << std::endl << std::endl;
    return 0;
}
