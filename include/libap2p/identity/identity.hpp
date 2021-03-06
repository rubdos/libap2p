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
     *  If no key is found on the default location, a new one is generated.
     *  cfr. Identity::GenerateLocal(std::string id)
     */
    void LoadLocal();

    /** Loads a key by its name.
     *
     */
    void LoadKey(std::string);
    /** Generates a local RSA key.
     *  Saves the key at specified filename.
     */
    void GenerateLocal(std::string filename);

    /** Checks wether the keys used are safe.
     *  @warning    Can take a while.
     *  @return     True when loaded key is methematically safe, false when it isn't.
     */
    bool ValidateKeys();

    /** Returns the Identities fingerprint.
     *  @return     The fingerprint of the associated public key
     */
    std::string GetFingerprint();

    /** Returns the base64 encoded public key.
     *  To be imported with CryptoPP::RSA::PrivateKey::Load();
     */
    std::string GetPublicKey();

    /** Loads a base64 encoded public key.
     *
     */
    void LoadPublicKey(std::string pk);

    /** Signs the message with the PrivateKey if available.
     *  Signs with PSS and SHA256, returns base64 encoded.
     *  @return     A signature of the message.
     */
    std::string Sign(std::string message);

    /** Verifies the message with the provided signature.
     *
     */
    bool Verify(std::string message, std::string signature);
private:
    /** Returns the default filename for a key on this system.
     *
     */
    std::string _GetDefaultKeyFilename();
    /** Returns the folder with keys stored.
     *
     */
    std::string _GetKeyFolder();

    CryptoPP::RSA::PrivateKey* _privateKey;
    CryptoPP::RSA::PublicKey*  _publicKey;

    std::string _publicKeyFingerprint;
};
}

#endif
