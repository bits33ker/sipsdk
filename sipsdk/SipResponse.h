#pragma once
#include "Sip.h"
namespace sip {
	class SipResponse :
		public Sip 
		//public SipString
	{
		int imethod;
		string method;
	public:
		SipResponse(int im, string m, string header, string body);
		virtual string to_string();

		virtual SipBase * clone();
		virtual bool isRequest();
	};
};
