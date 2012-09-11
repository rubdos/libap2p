#include "network/network.hpp"
#include "node/node.hpp"

#include <iostream>

using namespace std;

int main()
{
    // Open a basic configuration class with defaults (server port on 12011
    libap2p::configuration * conf = new libap2p::configuration();
    // Make server listen on port 12012, so you can connect to test_create_server
    conf->put("server.port", 12012);

    // Create a network and print its status
    libap2p::network *conn = new libap2p::network(conf);
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
    // Start main loop
    while(conn->status() == libap2p::CONNECTED)
    {
        //nop. This is a test
    }

    // Close and return
    conn->close();
    return 0;
}
