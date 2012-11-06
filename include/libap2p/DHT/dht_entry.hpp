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

#ifndef CLASS_DHT_ENTRY
#define CLASS_DHT_ENTRY

#include <string>
#include <vector>

#include "libap2p/identity/identity.hpp"

namespace libap2p
{
typedef std::vector<std::string> TagList;
class DHTEntry
{
public:
    /** Creates a new DHTEntry object in a network.
     *  @param name         The name of the DHTEntry
     *  @param contents     The contents of the DHTEntry
     *  @param taglist      A list with Tags associated with the object
     *  @param ttl          The time to live for the object: give the unix timestamp to die.
     *  @param owner        The owner/creator of the DHTEntry.
     */
    DHTEntry(std::string name,
            std::string contents,
            TagList taglist,
            unsigned long ttl,
            Identity* owner);


    TagList tags;
    std::string name;
    std::string data;
    unsigned long timeToLive;
    std::string signature;
};
}

#endif
