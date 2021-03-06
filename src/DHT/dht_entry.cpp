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
#include "libap2p/configuration/configuration.hpp"

#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string.hpp>

namespace fs=boost::filesystem;

namespace libap2p
{
DHTEntry::DHTEntry(std::string hash)
{
    this->hash = hash;
    this->_consistent = true;
    this->_partCount = 0;
    std::string dhtdirectory = std::string(getenv("HOME")) + "/.libap2p/dht/";
    if(fs::is_directory(dhtdirectory + hash))
    {
        if(!fs::exists(dhtdirectory + hash + "/properties.xml"))
            return;

        // Load it
        const unsigned int part_length = 200;
        std::ifstream properties;
        properties.open((dhtdirectory + hash + "/properties.xml").c_str());

        properties.seekg(0, std::ios::end);
        unsigned int filelength = properties.tellg();
        properties.seekg(0, std::ios::beg);

        boost::property_tree::ptree properties_xml;
        read_xml(properties, properties_xml);

        std::string buffer = properties_xml.get<std::string>("parts");
        std::vector<std::string> splitVec;

        boost::algorithm::split(splitVec, 
                buffer, 
                boost::algorithm::is_any_of("\n\r"),
                boost::algorithm::token_compress_on);
        for(std::vector<std::string>::iterator line_it = splitVec.begin();
                line_it != splitVec.end();
                ++line_it)
        {
            std::string partial_hash = line_it->substr(0, 64);

            this->_partList.push_back(partial_hash);
            this->_partCount++;

            if(!fs::exists(dhtdirectory + "data/" + partial_hash))
            {
                this->_consistent = false;
            }
        }
        this->hash = properties_xml.get<std::string>("hash");
        this->timeToLive = properties_xml.get<unsigned int>("ttl");
        this->name = properties_xml.get<std::string>("name");
    }
    else
    {
        // Create the directory and hope we'll find something on the network
        fs::create_directory(dhtdirectory + hash);
    }
}
DHTEntrySpec DHTEntry::GetDHTEntrySpec()
{
    DHTEntrySpec des;
    des.partCount = this->_partCount;
    des.parts = this->_partList;
    des.hash = this->hash;
    return des;
}
DHTEntry::DHTEntry(std::string name, 
        std::string filename, 
        TagList tl, 
        unsigned long ttl,
        Identity* owner,
        unsigned int part_length)
{
    this->name = name;
    this->tags = tl;
    this->timeToLive = ttl;
    this->_partCount = 0;

    CryptoPP::SHA256 total_hash;

    unsigned int new_bytes_read=0, file_length=0, total_read=0;

    std::ifstream file;
    file.open(filename.c_str(), std::ios::binary);

    file.seekg(0, std::ios::end);
    file_length = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<byte*> parts;

    std::string dhtdirectory = std::string(getenv("HOME")) + "/.libap2p/dht/";
    if(!fs::is_directory(dhtdirectory))
    {
        fs::create_directory(dhtdirectory);
    }
    if(!fs::is_directory(dhtdirectory + "data"))
    {
        fs::create_directory(dhtdirectory + "data");
    }

    fs::create_directory(dhtdirectory + "tmp");
    
    std::ofstream index;
    index.open((dhtdirectory + "tmp/index").c_str());

    std::stringstream serialized_parts;
    
    while(total_read < file_length)
    {
        CryptoPP::SHA256 partial_hash;
        unsigned int to_read = (file_length - total_read > part_length) ?
                part_length
                :
                (file_length - total_read);
        char* buffer = new char[to_read];
        file.read(buffer, to_read);
        total_read += to_read;
        new_bytes_read = to_read;
        
        total_hash.Update((byte*) buffer, new_bytes_read);
        partial_hash.Update((byte*) buffer, new_bytes_read);

        byte sub_digest[CryptoPP::SHA256::DIGESTSIZE];
        partial_hash.Final(sub_digest);
        parts.push_back(sub_digest);

        index.write((const char *) sub_digest, CryptoPP::SHA256::DIGESTSIZE);

        std::ofstream part_file;
        std::string sha;
        CryptoPP::HexEncoder encoder;

        encoder.Attach(new CryptoPP::StringSink(sha));
        encoder.Put(sub_digest, sizeof(sub_digest));
        encoder.MessageEnd();
        part_file.open((dhtdirectory + "data/" + sha).c_str());
        
        serialized_parts << sha << new_bytes_read << std::endl;

        part_file.write(buffer, new_bytes_read);
        part_file.close();

        this->_partList.push_back(sha);
        this->_partCount++;

        delete[] buffer;
    }

    byte digest[ CryptoPP::SHA256::DIGESTSIZE ];

    total_hash.Final(digest);

    CryptoPP::HexEncoder encoder;

    encoder.Attach(new CryptoPP::StringSink(this->hash));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    // Store the sha's and contents, use gzip
    std::string entrydir = dhtdirectory + this->hash + "/";
    if(fs::is_directory(entrydir))
    {
        // Already exists
        return;
    }
    else
    {
        fs::create_directory(entrydir);
        fs::rename(dhtdirectory + "tmp", entrydir);
    }
    index.close();
    file.close();

    // Safe the info.

    boost::property_tree::ptree info;
    info.put("hash", this->hash);
    info.put("ttl", this->timeToLive);
    info.put("name", this->name);
    info.put("parts", (byte *) serialized_parts.str().c_str());

    std::ofstream properties_xml;
    properties_xml.open((entrydir + "properties.xml").c_str());

    write_xml(properties_xml, info);
    properties_xml.close();
}
bool DHTEntry::CheckConsistency()
{
    return true;
}
}
