#pragma once
#include "Sip.h"

namespace sip {
	class UserAgent : public SipString
	{
		string user;
	public:
		UserAgent(string u);
		~UserAgent();

		virtual string to_string();
	};
}

