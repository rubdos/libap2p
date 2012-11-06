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

#include "libap2p/DHT/dht_entry.hpp"

namespace libap2p
{
DHTEntry::DHTEntry(std::string name, 
        std::string contents, 
        TagList tl, 
        unsigned long ttl,
        Identity* owner)
{
    this->name = name;
    this->data = contents;
    this->tags = tl;
    this->timeToLive = ttl;
}

}
