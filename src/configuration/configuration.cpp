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

#include "libap2p/configuration/configuration.hpp"

namespace libap2p
{

// Public
/** Loads the default configuration file(s)
 *  Merges into the configuration.
 */
void Configuration::LoadFile()
{
    //this->
    return;
    /*@todo: Add default configuration file here.
     *       filepath should be chosed on OS type:
     *       Unix:    .libap2p folder in home directory
     *       Windows: %APPDATA%/libap2p (though, who uses
     *                windows these days
     *       Mac:     Don't know. Hints?)
     */
}

/** Loads a configuration file specified by filename.
 *  Is merged into the configuration.
 *
 *  @throws: xml_parser_error when xml can't be parsed
 */
void Configuration::LoadFile(std::string filename)
{
    this->_lastFilename = filename;
    boost::property_tree::ptree cfg_file_pt;
    
    read_xml(filename, cfg_file_pt);

    this->_Merge(cfg_file_pt);
}

/** Saves the configuration to a file.
 *  Saves the configuration to the last loaded file in
 *  libap2p::configuration::load_file
 */
void Configuration::SaveFile()
{
    this->SaveFile(this->_lastFilename);
}

/** Saves the configuration to the specified file
 *  @param filename an std::string with the path to the
 *         writable filename to write to.
 */
void Configuration::SaveFile(std::string filename)
{
    boost::property_tree::xml_parser::write_xml(filename, *dynamic_cast<boost::property_tree::ptree*>(this));
}


// Private

/** Merges a property tree in the configuration
 *  @param pt the property tree to merge into the current configuration
 *  @note Internally called.
 */

void Configuration::_Merge(boost::property_tree::ptree pt)
{
    this->_Merge(pt, "");
}

void Configuration::_Merge(boost::property_tree::ptree pt, std::string prefix)
{
    using boost::property_tree::ptree;
    ptree::const_iterator end = pt.end();
    for (ptree::const_iterator it = pt.begin(); it != end; ++it) 
    {
        std::stringstream key;
        if(strlen(prefix.c_str()) > 0 )
        {
            key << prefix << ".";
        }
        key << it->first;
        // std::cout << "(" << key.str() << ": " << it->second.get_value<std::string>() << ")" << std::endl; // Uncomment to debug

        this->put(key.str(), it->second.get_value<std::string>());

        if(pt.get_child(it->first).size() > 0)
        {
            this->_Merge(pt.get_child( it->first ), key.str());
        }
    }
}
}
