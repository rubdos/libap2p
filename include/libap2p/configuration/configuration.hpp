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

#ifndef CLASS_CONFIGURATION
#define CLASS_CONFIGURATION

#include <boost/bind.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <string>

namespace libap2p
{
class Configuration : public boost::property_tree::ptree
{
public:
    void LoadFile();
    void LoadFile(std::string);

    void SaveFile();
    void SaveFile(std::string);
private:
    void _Merge(boost::property_tree::ptree);
    void _Merge(boost::property_tree::ptree, std::string);

    std::string _lastFilename;
};
}

#endif
