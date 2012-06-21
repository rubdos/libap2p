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

#include <iostream>
#include <sstream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

namespace libap2p
{

/**
* @brief Default constructor
*/
message::message()
{
    this->_init();
}

/**
* @brief Constructor with data.
* Used to prepare a message to be send 
* @param messagetype    Message type. Can be any uint. Will be send through the socket
* @param messagedata    The data to send. Easy construction by boost::asio::buffer([anything here]);
*/
message::message(unsigned int messagetype, std::string messagedata)
{
    this->_init();
    this->_message_type = messagetype;
    this->_message_data = messagedata;
}

/**
* @brief Constructor from XML content
* @param xml_str an std::string with xml contents.
*/
message::message(std::string xml_str)
{
    this->_init();

    std::stringstream in;
    in << xml_str;

    boost::property_tree::ptree pt;

    read_xml(in, pt);

    this->_message_version = pt.get<std::string>("libap2p.version");
    this->_message_data = pt.get<std::string>("libap2p.message.data");
    this->_message_type = pt.get<unsigned int>("libap2p.message.type");
    this->_message_signature = pt.get<std::string>("libap2p.signature.signature");
    this->_message_signature_type = pt.get<std::string>("libap2p.signature.type");
}

/** Initializes the message with default values. Internally and privately called
 *
 */
void message::_init()
{
        this->_message_signature = "";
        this->_message_signature_type = "";
        this->_message_type = 0;
        this->_message_data = "";
}

/**
* @brief Get the xml text for the message
* Internally used
* @return The xml-structure of the message.
*/
std::string message::get_xml()
{
    boost::property_tree::ptree pt;
    std::stringstream out;

    pt.put("libap2p.version", "0.0.1");
    pt.put("libap2p.message.type", this->_message_type);
    pt.put("libap2p.message.data", this->_message_data);
    pt.put("libap2p.signature.signature", this->_message_signature); //!todo: Check signature before sending?
    pt.put("libap2p.signature.type", this->_message_signature_type);
    
    write_xml(out, pt);
    
    return out.str();
}

void message::prepare()
{
    this->_compress();
}

void message::_compress()
{
    std::stringstream xml, compressedxml;
    xml << this->get_xml();

    boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
    in.push(boost::iostreams::gzip_compressor());
    in.push(xml);
    boost::iostreams::copy(in, this->_compressed);
}

header* message::get_header()
{
    header *hdr = new header();

    // Search message length:
    this->_compressed.seekp(0, std::ios::end);
    hdr->message_length = this->_compressed.tellp();
    this->_compressed.seekp(0, std::ios::beg);

    // Set compression system
    hdr->compression_flags = 1; //@todo: hardcoded to GZIP, FIXME

    return hdr;
}

std::string message::get_encoded()
{
    return this->_compressed.str();
}
}
