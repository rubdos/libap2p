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
    MESSAGE_IDENTIFY = 0

};
/** Represents the message header.
 *  Internally called.
 */
class header
{
public:
    header();
    header(int64_t);
    int64_t get_encoded();

    int32_t message_length;
    int8_t compression_flags;
private:
    int get_flags1();
    int get_flags2();
    int get_flags3();
    bool get_bit(unsigned char, unsigned char);
};
}

#endif
