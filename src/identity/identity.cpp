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
#include <cryptopp/base64.h>
#include <cryptopp/hex.h>

#include <stdio.h>
#include <stdlib.h> // For getenv

#include <iostream>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace libap2p
{
Identity::Identity()
{
    this->_publicKey = NULL;
    this->_privateKey = NULL;
    //@TODO: stub
}
bool Identity::ValidateKeys()
{
    // Open a random generator
    CryptoPP::AutoSeededRandomPool rng;

    if(this->_privateKey == NULL || this->_publicKey == NULL)
    {
        return false;
    }
    
    return (
            this->_privateKey->Validate(rng, 3) // 3 = high security level.
            &&
            this->_publicKey->Validate(rng, 3) // Idem
            );
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

    while(!this->ValidateKeys())
    {
        // Generate Parameters
        CryptoPP::InvertibleRSAFunction params;
        params.GenerateRandomWithKeySize(rng, 3072);

        // Create Keys
        this->_privateKey = new CryptoPP::RSA::PrivateKey(params);
        this->_publicKey  = new CryptoPP::RSA::PublicKey(params);

        std::clog << "Validating security of the keypair" << std::endl;
    }

    CryptoPP::FileSink pubfile( (filename + ".pub").c_str() );
    CryptoPP::FileSink privfile( (filename + ".prv").c_str() );

    this->_publicKey->Save(pubfile);
    this->_privateKey->Save(privfile);

    std::clog << "Saved the keys" << std::endl;
}
void Identity::LoadLocal()
{
    if(fs::exists(this->_GetDefaultKeyFilename() + ".pub") &&
            fs::exists(this->_GetDefaultKeyFilename() + ".prv")
            )
    {
        // Load it;
        this->_LoadLocal();
    }
    else
    {
        // Generate it;
        this->GenerateLocal();
    }
    std::clog << "Loaded RSA key: " << this->GetFingerprint() << std::endl;
}
std::string Identity::GetFingerprint()
{
    if(this->_publicKeyFingerprint.compare("") == 0)
    {
        if(this->_publicKey == NULL)
        {
            return "";
        }
        
        // Load the keys fingerprint (=sha256(pk))
        CryptoPP::SHA256 hash;
        std::string pk;

        this->_publicKey->Save(CryptoPP::StringSink(pk).Ref());

        CryptoPP::StringSource pkss(pk, true,
                new CryptoPP::HashFilter(hash,
                    new CryptoPP::HexEncoder (
                        new CryptoPP::StringSink(this->_publicKeyFingerprint), true, 2, ":")));
    }
    return this->_publicKeyFingerprint;
}
void Identity::_LoadLocal()
{
    
}
std::string Identity::_GetDefaultKeyFilename()
{
    return std::string(getenv("HOME")) + "/.libap2p/default_key";
}
}
