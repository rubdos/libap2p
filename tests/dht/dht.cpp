#include "libap2p/DHT/dht_entry.hpp"
#include "libap2p/DHT/dht.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cerr << "Syntax: " << std::endl <<
            argv[0] << " [filename]" << std::endl;
        return -1;
    }
    libap2p::TagList tl;
    libap2p::DHTEntry de("testentry",
            std::string(argv[1]),
            tl,
            0,
            NULL, // No owner yet.
            1024*1024);
    return 0;
}
