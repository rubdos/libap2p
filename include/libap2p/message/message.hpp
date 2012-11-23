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
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/asio.hpp>

#include "libap2p/message/header.hpp"
#include "libap2p/identity/identity.hpp"

namespace libap2p
{
class Message
{
public:
    Message();
    Message(message_types /* message type */, std::string /* data */);
    Message(std::string /* xml */);
    Message(std::vector<char> /* message compressed */, Header*);

    /** Sign the message data before sending.
     *  @note   Call before Prepare()
     *  @param  id  The identity with a private key to sign the data with.
     */
    void Sign(Identity* id);
    void Prepare();

    message_types GetMessageType();
    
    std::string GetXml();
    Header *GetHeader();
    boost::asio::streambuf* GetEncoded();
    /** Get the data stored in the message
     *
     */
    std::string GetData();
private:
    void _Init();
    void _Init(std::string /* xml */);
    void _Compress();

    boost::asio::streambuf _compressedBuf;

    std::string _messageVersion;

    message_types _messageType;
    std::string _messageData;
    std::string _messageSignature;
    std::string _messageSignatureType;
};
}
#endif
