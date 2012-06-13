#include "network/network.hpp"

#include <iostream>

using namespace std;

int main()
{
	libap2p::network *conn = new libap2p::network();
	cout << conn->status() << endl;
	conn->connect();
	cout << conn->status() << endl;
	return 0;
}
