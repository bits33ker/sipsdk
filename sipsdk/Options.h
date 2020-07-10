#pragma once
#include "Request.h"
namespace sip {
	class Options :
		public Request
	{
		string method;
	public:
		Options(string suri, string sheader, string sbody);
		virtual string getMethod() { return method; };
	};
};
