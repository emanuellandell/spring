#ifndef _LOCALCONNECTION 
#define _LOCALCONNECTION

#include <boost/thread/mutex.hpp>
#include <queue>

#include "Connection.h"
#include "RawPacket.h"

namespace netcode {

/**
@brief Class for local connection between server / client
Directly connects to each others inputbuffer to increase performance. The server and the client have to run in one instance of spring for this to work, otherwise a normal UDP connection had to be used.
IMPORTANT: You must not have more than two instances of this
 */
class CLocalConnection : public CConnection
{
public:
	/**
	@brief Constructor
	@throw network_error When there already 2 instances
	*/
	CLocalConnection();
	virtual ~CLocalConnection();
	
	/**
	@brief Send data to other instance
	*/
	virtual void SendData(const unsigned char *data, const unsigned length);
	
	/**
	@brief Get data
	*/
	virtual RawPacket* GetData();

	/// does nothing
	virtual void Flush(const bool forced = false);
	
	/// is always false
	virtual bool CheckTimeout() const;

private:
	static std::queue<RawPacket*> Data[2];
	static boost::mutex Mutex[2];

	unsigned OtherInstance() const;

	/// we can have 2 Instances, one in serverNet and one in net
	static unsigned Instances;
	/// which instance we are
	unsigned instance;
};

} // namespace netcode

#endif
