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

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace libap2p
{
class message
{
public:
    message();
    message(unsigned int /* message type */, std::string /* data */);
    message(std::string /* xml */);
    
    std::string get_xml();
private:
    void _init();

    std::string _message_version;

    unsigned int _message_type;
    std::string _message_data;
    std::string _message_signature;
    std::string _message_signature_type;
};
}
#endif
