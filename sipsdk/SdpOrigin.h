#pragma once
#include "sipsdk.h"
#include "SipString.h"

#include <string>
using namespace std;

namespace sip {
	class SIPSDK SdpOrigin :
		public SipString
	{
		string username;//login name
		string session_id;
		string session_version;
		string net_type;
		string addr_type;
		string address;
	public:
		
		SdpOrigin(string content);
		~SdpOrigin();

		virtual string to_string();
	};
};
