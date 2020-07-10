#pragma once
#include "Request.h"

namespace sip {
	class SIPSDK Invite : public Request
	{
		string method;
	public:
		Invite(string suri, string sheader, string sbody);
		virtual string getMethod() { return method; };
	};
}