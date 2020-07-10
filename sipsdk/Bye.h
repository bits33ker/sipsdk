#pragma once
#include "Request.h"
namespace sip {
	class Bye :
		public Request
	{
		string method;
	public:
		Bye(string suri, string sheader, string sbody);
		virtual string getMethod() { return method; };
	};
};
