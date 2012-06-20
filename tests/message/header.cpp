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
#include <stdio.h>
#include <iostream>
#include <stdint.h>


int main()
{
    std::cout << "Preparing header with message_length of 1KB, compression GZIP, flags all 0" << std::endl;
    libap2p::header* hdr = new libap2p::header();
    hdr->message_length = 1024; // Lets set message length to be a kilobyte.
    hdr->compression_flags = libap2p::GZIP; // And lets try GZIP
    std::cout << "Header (try to read the binary form ;) ): ";
    int64_t enc = hdr->get_encoded();

    std::cout << enc << std::endl;

    std::cout << "Decoding header" << std::endl;
    hdr = new libap2p::header(enc);
    std::cout << "Message length: " << hdr->message_length << std::endl
        << "Message compression type (1=GZIP): " << (int)hdr->compression_flags << std::endl;
    return 0;
}
