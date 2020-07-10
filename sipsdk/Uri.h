#pragma once
#include "sipsdk.h"
#include "SipString.h"

namespace sip {
	class SIPSDK Uri : public SipString
	{
	public:
		virtual string getUser() = 0;
		virtual string getIp() = 0; 
		virtual int getPort() = 0;
		//virtual string getTag() = 0;

		virtual string operator=(string u) = 0;
	};
}
