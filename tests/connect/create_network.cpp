#include "libap2p/network/network.hpp"

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
void _nodeConnected(libap2p::Node* nd)
{
    std::cout << "A node has connected" << std::endl;
}

int main()
{
    // Open a basic configuration class with defaults (server port on 12011)
    libap2p::Configuration * conf = new libap2p::Configuration();

    // Create a network and print its status
    libap2p::Network *conn = new libap2p::Network(conf);
    cout << "initial network::connection_status: " <<  conn->Status() << endl;

    // Subscribe to the correct signals
    conn->onReceiveMessage.connect(_receiveMessage);
    conn->onNodeConnect.connect(_nodeConnected);

    // Connect to the network and print its status
    conn->Connect();
    cout << "network::connection_status after connect(): " << conn->Status() << endl;


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
    // Start the main loop
    while(conn->Status() == libap2p::CONNECTED)
    {
        //nop. This is a test...
    }

    // Close and return
    conn->Close();
    return 0;
}
