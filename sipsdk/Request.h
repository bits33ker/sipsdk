#pragma once
#include "Sip.h"
#include "SipRequest.h"
namespace sip {
	class Request :
		public SipRequest, Sip
	{
		string method;
		unique_ptr<Uri>uri;
	public:
		Request(string suri, string sheader, string sbody);
		virtual Uri * getSipUri() { return uri.get(); };
		virtual int getMaxForwards();

		virtual HeaderContact * getFrom()override { return Sip::getFrom(); };
		virtual HeaderContact * getTo()override { return Sip::getTo(); };
		virtual Via * getVia()override { return Sip::getVia(); };
		virtual SipString * getHeader(string c)override { return Sip::getHeader(c); };
		virtual Sip *clone();

		virtual string to_string();
	};
};
