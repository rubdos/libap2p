#include "libap2p/identity/identity.hpp"

#include <iostream>
#include <stdlib.h>
#include <string.h>

int main()
{
    std::cout << "Loading keys." << std::endl;

    libap2p::Identity id;
    id.LoadLocal();

    std::string plaintext = "Hello World. Libap2p now does encryption.",
        signature, cyphertext;


    std::cout << "Plaintext:" << std::endl << plaintext << std::endl;

    signature = id.Sign(plaintext);

    std::cout << "Signature:" << std::endl << signature << std::endl;


    return 0;
}
