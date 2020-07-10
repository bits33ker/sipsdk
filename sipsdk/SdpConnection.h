#pragma once
#include "sipsdk.h"
#include "SipString.h"

#include <string>
using namespace std;

namespace sip {
	class SIPSDK SdpConnection :
		public SipString
	{
		string net_type;
		string addr_type;
		string address;
	public:
		SdpConnection(string content);
		~SdpConnection();

		virtual string to_string();
	};

};