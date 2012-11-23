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
#include "libap2p/DHT/dht.hpp"
namespace libap2p
{
DHT::DHT()
{
    // We're lazy. Don't do anything!
}
DHTEntry* DHT::Fetch(std::string sha256sum)
{
    if(sha256sum.length() != 64) return NULL; // All sha256sums are 32byte/64nibbles
    for(DHTEntryList::iterator de_it = this->_entries.begin();
            de_it != this->_entries.end();
            ++de_it)
    {
        if((*de_it)->hash.compare(sha256sum) == 0)
        {
            return *de_it;
        }
    }
}
void DHT::AddEntry(DHTEntry* entry, bool check_consistency)
{
    if(entry == NULL) return;
    this->_entries.push_back(entry);

    if(check_consistency)
    {
        entry->CheckConsistency();
    }
}
}
