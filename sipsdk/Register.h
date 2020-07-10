#pragma once
#include "Request.h"

namespace sip {
	class Register :
		public Request
	{
		string method;
	public:
		Register(string suri, string sheader, string sbody);
		virtual string getMethod() { return method; };
	};
};
