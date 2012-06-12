
namespace libap2p
{
enum connection_status { CONNECTED, CONNECTING, DISCONNECTED, ERROR}
class network
{
public:
	void connect();


	network(): status(_connection_status){}
	const connection_status &status;
private:
	connection_status _connection_status;
}
}
