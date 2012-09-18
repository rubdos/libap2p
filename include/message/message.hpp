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

#ifndef CLASS_MESSAGE
#define CLASS_MESSAGE

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/asio.hpp>

#include "message/header.hpp"

namespace libap2p
{
class message
{
public:
    message();
    message(message_types /* message type */, std::string /* data */);
    message(std::string /* xml */);
    message(boost::asio::streambuf* /* message compressed */, header*);

    void prepare();

    message_types GetMessageType();
    
    std::string get_xml();
    header *get_header();
    boost::asio::streambuf* get_encoded();
private:
    void _init();
    void _init(std::string /* xml */);
    void _compress();

    boost::asio::streambuf _compressed_buf;

    std::string _message_version;

    message_types _message_type;
    std::string _message_data;
    std::string _message_signature;
    std::string _message_signature_type;
};
}
#endif
