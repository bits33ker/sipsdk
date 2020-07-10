#pragma once
#include "sipsdk.h"
#include "SipString.h"
#include <string>
using namespace std;

namespace sip {
	class SIPSDK SdpVersion : public SipString
	{
		int version;
	public:
		SdpVersion(string content);
		~SdpVersion();

		virtual string to_string();
	};

};