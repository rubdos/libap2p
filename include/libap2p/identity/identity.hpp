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

#ifndef CLASS_IDENTITY
#define CLASS_IDENTITY

#include <string>

#include <cryptopp/rsa.h>


namespace libap2p
{
class Identity
{
public:
    Identity();
    /** Loads a locally stored identity.
     *  Will load the identity stored on the default place on the harddisk.
     *  If no key is found on the default location, a new one is generated. See Identity::GenerateLocal()
     */
    void LoadLocal();
    /** Generates a local RSA key.
     *  Generates a local RSA 3072 key at default location: $HOME/.libap2p/default_key.
     */
    void GenerateLocal();
    /** Generates a local RSA key.
     *  Saves the key at specified filename.
     */
    void GenerateLocal(std::string filename);

    bool ValidateKeys();
private:
    /** Returns the default filename for a key on this system.
     *
     */
    std::string _GetDefaultKeyFilename();
    void _LoadLocal();

    CryptoPP::RSA::PrivateKey* _privateKey;
    CryptoPP::RSA::PublicKey*  _publicKey;
};
}

#endif
