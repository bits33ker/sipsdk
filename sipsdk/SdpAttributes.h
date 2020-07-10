#pragma once
#include "sipsdk.h"
#include "SipString.h"

#include <string>
using namespace std;

namespace sip {
	namespace sdp_attr {
		const string rtpmap = "rtpmap";
		const string fmtp = "fmtp";
	}
	class SIPSDK SdpAttributes :
		public SipString
	{
		string name;
		string attr;
	public:
		SdpAttributes(string content);
		~SdpAttributes();

		virtual string to_string();
	};
};
