#include "network/network.hpp"

#include <iostream>

using namespace std;

int main()
{
    // Create a network and print its status
    libap2p::network *conn = new libap2p::network();
    cout << "initial network::connection_status: " <<  conn->status() << endl;

    // Connect to the network and print its status
    conn->connect();
    cout << "network::connection_status after connect(): " << conn->status() << endl;


    if(conn->status() == libap2p::CONNECTING)
    {
        cout << "libap2p::network is connecting..." << endl;
        while(conn->status() == libap2p::CONNECTING)
        {
            //nop...
        }
        if(conn->status() != libap2p::CONNECTED)
        {
            cout << "error connecting to the network";
        }
    }

    // Close and return
    conn->close();
    return 0;
}
