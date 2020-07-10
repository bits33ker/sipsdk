#include "SdpOrigin.h"
#include "SessionDescription.h"

namespace sip {
	SdpOrigin::SdpOrigin(string content)
	{
		//o=<username> <sess-id> <sess-version> <nettype> <addrtype> <unicast - address>
		size_t pos = content.find(" ");
		username = content.substr(0, pos);

		size_t pos2 = content.find(" ", pos + 1);
		session_id = content.substr(pos + 1, pos2 - pos - 1);
		pos = pos2;

		pos2 = content.find(" ", pos + 1);
		session_version = content.substr(pos + 1, pos2 - pos - 1);
		pos = pos2;

		pos2 = content.find(" ", pos + 1);
		net_type = content.substr(pos + 1, pos2 - pos - 1);
		pos = pos2;

		pos2 = content.find(" ", pos + 1);
		addr_type = content.substr(pos + 1, pos2 - pos - 1);
		pos = pos2;

		address = content.substr(pos + 1, content.length() - pos);
	}


	SdpOrigin::~SdpOrigin()
	{
	}

	string SdpOrigin::to_string()
	{
		//string owner = "o=5409 0 0 IN IP4 192.168.41.227\r\n";
		return constSdp::sdpOrigin + constSdp::kvoperator + username + " "
			+ session_id + " " + session_version + " " + net_type + " "
			+ addr_type + " " + address;
	}
}