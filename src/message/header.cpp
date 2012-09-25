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

#include "libap2p/message/header.hpp"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

namespace libap2p
{
// Public

Header::Header()
{
    this->compressionFlags = COMPRESSION_NONE;
}
/** Header constructor from an int64_t received header.
 *  
 */
Header::Header(int64_t str_header)
{
    int8_t flags1, flags2, flags3, _compression_flags;

    _compression_flags = (int8_t) str_header;
    this->compressionFlags = _compression_flags;
    
    str_header >>= 8;
    flags3 = str_header;
    
    str_header >>=8;
    flags2 = str_header;
    
    str_header >>=8;
    flags1 = str_header;
    
    str_header >>=8;
    this->messageLength = str_header;
}

/** Encodes the message header for postal.
 *  @return An unsigned char array 7 bytes long. First four bytes
 *          are message length. Then flags 1 and flags 2 and
 *          compression flags. See wiki/protocol specification.
 */
int64_t Header::GetEncoded()
{
    int64_t encoded = (int64_t) this->messageLength;
    encoded <<= 8; // sizeof flag is 8 bits
    encoded += this->_GetFlags1();
    encoded <<= 8;
    encoded += this->_GetFlags2();
    encoded <<= 8;
    encoded += this->_GetFlags3();
    encoded <<= 8;
    encoded += this->compressionFlags;
    
    return encoded;
}


// Private

/**
 *
 */
int Header::_GetFlags1()
{
    return 0;
}
/**
 *
 */
int Header::_GetFlags2()
{
    return 0;
}
/**
 *
 */
int Header::_GetFlags3()
{
    return 0;
}

/** Gets a single bit state of a byte.
 *  @param number   The char of which the bit is taken
 *  @param position The position where the bit is taken
 */
bool Header::GetBit(unsigned char number, unsigned char position) {
    unsigned char bitmask = 1 << position;
    return (number & bitmask) ? true : false;
}
}
