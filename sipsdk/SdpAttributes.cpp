#include "SdpAttributes.h"
#include "SessionDescription.h"

namespace sip {
	SdpAttributes::SdpAttributes(string content)
	{
		//"a=sendrecv\r\n";
		//"a=rtpmap:0 PCMU/8000/1\r\n";
		//"a=rtpmap:101 telephone-event/8000\r\n";
		//"a=fmtp:101 0-15\r\n";
		int pos = content.find(":");
		if (pos >= 0)
		{
			name = content.substr(0, pos);
			//if(name==sdp_attr::rtpmap)
			attr = content.substr(pos + 1, content.length() - pos - 1);
		}
		else
			name = content;
	}

	SdpAttributes::~SdpAttributes()
	{
	}

	string SdpAttributes::to_string()
	{
		string result = constSdp::sdpMediaAttr + constSdp::kvoperator
			+ name;
		if (!attr.empty())
			result = result + " " + attr;
		return result;
	}
}
