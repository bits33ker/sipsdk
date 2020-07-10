#include "SdpConnection.h"
#include "SessionDescription.h"

namespace sip {
	SdpConnection::SdpConnection(string content)
	{
		//"c=IN IP4 192.168.41.227\r\n";
		size_t pos = content.find(" ");
		net_type = content.substr(0, pos);

		size_t pos2 = content.find(" ", pos + 1);
		addr_type = content.substr(pos + 1, pos2 - pos - 1);
		pos = pos2;

		address = content.substr(pos + 1, content.length() - pos);
	}


	SdpConnection::~SdpConnection()
	{
	}

	string SdpConnection::to_string()
	{
		return constSdp::sdpConnection + constSdp::kvoperator
			+ net_type + " " + addr_type + " " + address;
	}
}