#include "libap2p/network/network.hpp"
#include "libap2p/node/node.hpp"

#include <iostream>

using namespace std;

void _receiveMessage(libap2p::Message* msg, libap2p::Node* nd)
{
        std::cout << std::endl << "Received a message" << std::endl
            << "------------------------------------------" << std::endl
            << "XML: " << std::endl
            << msg->GetXml() << std::endl
            << "------------------------------------------" << std::endl
            << "End XML" << std::endl << std::endl;
}

int main()
{
    // Open a basic configuration class with defaults (server port on 12011
    libap2p::Configuration * conf = new libap2p::Configuration();
    // Make server listen on port 12012, so you can connect to test_create_server
    conf->put("server.port", 12012);

    // Create a network and print its status
    libap2p::Network *conn = new libap2p::Network(conf);
    cout << "initial network::connection_status: " <<  conn->Status() << endl;

    // Subscribe to the correct events
    conn->onReceiveMessage.connect(_receiveMessage);

    // Connect to the network and print its status
    conn->Connect();
    cout << "network::connection_status after connect(): " << conn->Status() << endl;

    libap2p::ClientNodeConnection* cnc = 
        new libap2p::ClientNodeConnection("localhost", "12011"); // Construct the node connection
    libap2p::Node* n= new libap2p::Node(cnc); // Construct the node using the connection

    cnc->Connect();

    conn->AddNode(n);


    if(conn->Status() == libap2p::CONNECTING)
    {
        cout << "libap2p::network is connecting..." << endl;
        while(conn->Status() == libap2p::CONNECTING)
        {
            //nop...
        }
        if(conn->Status() != libap2p::CONNECTED)
        {
            cout << "error connecting to the network";
        }
    }
    // Start main loop
    while(conn->Status() == libap2p::CONNECTED)
    {
        //nop. This is a test
    }

    // Close and return
    conn->Close();
    return 0;
}
