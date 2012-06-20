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

namespace libap2p
{
// Public

header::header(const char* str_header)
{
}


// Private

/** Gets a single bit state of a byte.
 *  @param number   The char of which the bit is taken
 *  @param position The position where the bit is taken
 */
bool header::get_bit(unsigned char number, unsigned char position) {
    unsigned char bitmask = 1 << position;
    return (number & bitmask) ? true : false;
}
}
