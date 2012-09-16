#include "network/network.hpp"

#include <iostream>

using namespace std;

void _receiveMessage(libap2p::message* msg, libap2p::node* nd)
{
    std::cout << "Received a message" << std::endl;
}
void _nodeConnected(libap2p::node* nd)
{
    std::cout << "A node has connected " << std::endl;
}

int main()
{
    // Open a basic configuration class with defaults (server port on 12011)
    libap2p::configuration * conf = new libap2p::configuration();

    // Create a network and print its status
    libap2p::network *conn = new libap2p::network(conf);
    cout << "initial network::connection_status: " <<  conn->status() << endl;

    // Subscribe to the correct signals
    conn->onReceiveMessage.connect(_receiveMessage);
    conn->onNodeConnect.connect(_nodeConnected);

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
    // Start the main loop
    while(conn->status() == libap2p::CONNECTED)
    {
        //nop. This is a test...
    }

    // Close and return
    conn->close();
    return 0;
}
