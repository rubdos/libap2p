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

#include "libap2p/message/message.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include <cryptopp/gzip.h>
#include <cryptopp/filters.h>

namespace libap2p
{

/**
* @brief Default constructor
*/
Message::Message()
{
    this->_Init();
}

/**
* @brief Constructor with data.
* Used to prepare a message to be send 
* @param messagetype    Message type. Can be any uint. Will be send through the socket
* @param messagedata    The data to send. Easy construction by boost::asio::buffer([anything here]);
*/
Message::Message(message_types messagetype, std::string messagedata)
{
    this->_Init();
    this->_messageType = messagetype;
    this->_messageData = messagedata;
}

/** Constructor from XML content.
*   @param xml_str an std::string with xml contents.
*/
Message::Message(std::string xml_str)
{
    this->_Init(xml_str);
}

/** Constructor from compressed xml data and header.
 *
 */
Message::Message(std::vector<char> message_raw, Header* hdr)
{
    std::string xml;
    std::stringstream compressed;

    std::copy(message_raw.begin(), 
            message_raw.end(),
            std::ostream_iterator<char>(
                compressed
                )
            );
    
    try
    {
        CryptoPP::StringSource ss(compressed.str(),
            true, //pumpAll
            new CryptoPP::Gunzip (
                new CryptoPP::StringSink(xml)
            )
        );
        
        this->_Init(xml);
    }
    catch( boost::iostreams::gzip_error& e)
    {
        std::cerr << "GZIP error: " << e.error()  << "message length: " << hdr->messageLength << std::endl;
    }
}

boost::property_tree::ptree Message::GetMessageTree()
{
    return this->_pt;
}

/** Initializes from xml data.
 *
 */
void Message::_Init(std::string xml)
{
    this->_Init(); // Set default properties/..
    std::stringstream in;
    in << xml;

    read_xml(in, this->_pt);

    this->_messageVersion = this->_pt.get<std::string>("libap2p.version");
    this->_messageData = this->_pt.get<std::string>("libap2p.message.data");
    this->_messageType = (message_types) 
        this->_pt.get<unsigned int>("libap2p.message.type");
    this->_messageSignature = this->_pt.get<std::string>("libap2p.signature.signature");
    this->_messageSignatureType = this->_pt.get<std::string>("libap2p.signature.type");
}

/** Initializes the message with default values. Internally and privately called
 *
 */
void Message::_Init()
{
    this->_messageSignature = "";
    this->_messageSignatureType = "";
    this->_messageType = MESSAGE_HELLO;
    this->_messageData = "";
}

/** Get the xml text for the message.
*   Internally used
*   @return The xml-structure of the message.
*/
std::string Message::GetXml()
{
    std::stringstream out;

    this->_pt.put("libap2p.version", "0.0.1");
    this->_pt.put("libap2p.message.type", this->_messageType);
    this->_pt.put("libap2p.message.data", this->_messageData);
    this->_pt.put("libap2p.signature.signature", this->_messageSignature); //!todo: Check signature before sending?
    this->_pt.put("libap2p.signature.type", this->_messageSignatureType);
    
    write_xml(out, this->_pt);
    
    return out.str();
}

message_types Message::GetMessageType()
{
    return this->_messageType;
}
std::string Message::GetData()
{
    return this->_messageData;
}
void Message::Sign(Identity* id)
{
    this->_messageSignature = id->Sign(this->_messageData);
    this->GetXml(); // Update the pt;
}
void Message::Prepare()
{
    this->_Compress();
    this->GetXml(); // Update the pt;
}

void Message::_Compress()
{
    std::string compressed;
    CryptoPP::StringSource ss(this->GetXml(),
        true, // pumpAll
        new CryptoPP::Gzip (
            new CryptoPP::StringSink(compressed),
            5 // Compression level between 1 (fast) and 9 (compact)
        )
    );

    std::ostream compressed_buffer(&this->_compressedBuf);

    compressed_buffer << compressed << std::flush;

    this->_compressedBuf.commit(compressed.size());
    this->GetXml(); // Update the pt;
}

Header* Message::GetHeader()
{
    Header *hdr = new Header();

    // Search message length:
    hdr->messageLength = this->_compressedBuf.size();

    // Set compression system
    hdr->compressionFlags = 1; //@todo: hardcoded to GZIP, FIXME

    return hdr;
}

boost::asio::streambuf* Message::GetEncoded()
{
    return &(this->_compressedBuf);
}
}
