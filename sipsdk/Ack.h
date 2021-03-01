#pragma once
#include "Sip.h"
#include "Request.h"

namespace sip {
	class Ack :
		public Request
	{
		string method;
	public:
		Ack(string suri, string sheader, string sbody);
		virtual string getMethod() { return method; };
	};
};