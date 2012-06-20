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

#include "message/header.hpp"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

namespace libap2p
{
// Public

header::header()
{
    this->compression_flags = COMPRESSION_NONE;
}

header::header(int64_t str_header)
{
    int8_t flags1, flags2, flags3, _compression_flags;

    _compression_flags = (int8_t) str_header;
    this->compression_flags = _compression_flags;
    
    str_header >>= 8;
    flags3 = str_header;
    
    str_header >>=8;
    flags2 = str_header;
    
    str_header >>=8;
    flags1 = str_header;
    
    str_header >>=8;
    this->message_length = str_header;
}

/** Encodes the message header for postal.
 *  @return An unsigned char array 7 bytes long. First four bytes
 *          are message length. Then flags 1 and flags 2 and
 *          compression flags. See wiki/protocol specification.
 */
int64_t header::get_encoded()
{
    int64_t encoded = (int64_t) this->message_length;    
    encoded <<= 8; // sizeof flag is 8 bits
    encoded += this->get_flags1();
    encoded <<= 8;
    encoded += this->get_flags2();
    encoded <<= 8;
    encoded += this->get_flags3();
    encoded <<= 8;
    encoded += this->compression_flags;
    
    return encoded ;
}


// Private

/**
 *
 */
int header::get_flags1()
{
    return 0;
}
/**
 *
 */
int header::get_flags2()
{
    return 0;
}
/**
 *
 */
int header::get_flags3()
{
    return 0;
}

/** Gets a single bit state of a byte.
 *  @param number   The char of which the bit is taken
 *  @param position The position where the bit is taken
 */
bool header::get_bit(unsigned char number, unsigned char position) {
    unsigned char bitmask = 1 << position;
    return (number & bitmask) ? true : false;
}
}
