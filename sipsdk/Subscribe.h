#pragma once
#include "Request.h"
namespace sip {
	class Subscribe :
		public Request
	{
		string method;
	public:
		Subscribe(string suri, string sheader, string sbody);
		virtual string getMethod() { return method; };
	};
};
