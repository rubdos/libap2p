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

#ifndef CLASS_DHT
#define CLASS_DHT

#include "libap2p/DHT/dht_entry.hpp"

#include <string>
#include <vector>

namespace libap2p
{
typedef std::vector<DHTEntry*> DHTEntryList;
typedef std::vector<DHTEntrySpec> DHTSearchResult;
class DHT
{
public:
    DHT();
    DHTEntry* Fetch(std::string sha256sum);

    void AddEntry(DHTEntry* entry, bool check_consistency = true);
    DHTSearchResult LocalSearch(std::string);
private:
    DHTEntryList _entries;
};
}
#endif
