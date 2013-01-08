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

#ifndef CLASS_HEADER
#define CLASS_HEADER

#include <stdint.h>

namespace libap2p
{
enum compression_flags {
    COMPRESSION_NONE = 0,
    COMPRESSION_GZIP = 1
};

enum message_types
{
    MESSAGE_HELLO               = 0,    /**<Send a hello to the peer, included public key.*/
    MESSAGE_IDENTIFY_REQUEST    = 1,    /**<Ask the peer to identify itself.*/
    MESSAGE_IDENTIFY_RESPONSE   = 2,    /**<Return a signed version of the identification request.*/
    
    MESSAGE_NODES_REQUEST       = 3,    /**<Ask the corresponding node to send it's node list. */
    MESSAGE_NODES_RESPONSE      = 4,    /**<Data contains a list with nodes. */
    
    MESSAGE_NODE_INFO_REQUEST   = 5,    /**<Request info about a node. */
    MESSAGE_NODE_INFO_RESPONSE  = 6,    /**<Data contains pk, ip, port of the node. */
    
    MESSAGE_DATA                = 10,   /**<Send a message with data 
                                         * (library does not catch this, it's "end-user" data. */

    MESSAGE_DHT_SEARCH          = 21,    /**<Searches the Node for a DHTEntry with the tags*/
    MESSAGE_DHT_INFO            = 22,    /**<Fetches info about a DHTEntry object */
    MESSAGE_DHT_FETCH           = 23,    /**<Fetches the DHTEntry object part */
    MESSAGE_DHT_SEARCH_RESULT   = 24,    /**<Returns the result of a DHT_SEARCH */
    MESSAGE_DHT_INFO_RESULT     = 25,    /**<Returns the result of an info request */
    MESSAGE_DHT_PUSH            = 26,    /**<The answer on a DHT_FETCH */
};
/** Represents the message header.
 *  Internally called.
 */
class Header
{
public:
    Header();
    Header(int64_t);
    int64_t GetEncoded();

    int32_t messageLength;
    int8_t compressionFlags;
private:
    int _GetFlags1();
    int _GetFlags2();
    int _GetFlags3();
    bool GetBit(unsigned char, unsigned char);
};
}

#endif
