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

#include "libap2p/identity/identity.hpp"

#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>

#include <stdio.h>
#include <stdlib.h> // For getenv

#include <iostream>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace libap2p
{
Identity::Identity()
{
    
    //@TODO: stub
}
void Identity::GenerateLocal()
{
    // Create the directory containing the ap2p configuration if not exists.
    // @TODO: Move to libap2p::Configuration
    if(!fs::is_directory( std::string(getenv("HOME")) + "/.libap2p" ))
    {
        fs::create_directory(std::string(getenv("HOME")) + "/.libap2p");
    }
    this->GenerateLocal( this->_GetDefaultKeyFilename() );
    //@TODO: X-Platform; linux only
}
void Identity::GenerateLocal(std::string filename)
{
    std::clog << "Generating a new 3072 bit keypair, this can take a minute or two." << std::endl;
    std::clog << "Speed up the process by moving the mouse and generating general randomness" << std::endl;

    // Open a random generator
    CryptoPP::AutoSeededRandomPool rng;

    // Generate Parameters
    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, 3072);

    // Create Keys
    CryptoPP::RSA::PrivateKey privateKey(params);
    CryptoPP::RSA::PublicKey publicKey(params);

    CryptoPP::FileSink pubfile( (filename + ".pub").c_str() );
    CryptoPP::FileSink privfile( (filename + ".prv").c_str() );

    publicKey.Save(pubfile);
    privateKey.Save(privfile);
}
void Identity::LoadLocal()
{
    if(fs::exists(this->_GetDefaultKeyFilename() + ".pub") &&
            fs::exists(this->_GetDefaultKeyFilename() + ".prv")
            )
    {
        // Load it;
    }
    else
    {
        // Generate it;
        this->GenerateLocal();
    }
}
std::string Identity::_GetDefaultKeyFilename()
{
    return std::string(getenv("HOME")) + "/.libap2p/default_key";
}
}
