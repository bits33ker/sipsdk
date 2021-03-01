#include "SipResponse.h"
#include "SipException.h"


namespace sip {
	SipResponse::SipResponse(int im, string m, string header, string body)
		:Sip(header, body)
	{
		imethod = im;
		method = m;
	}

	SipBase *SipResponse::clone()
	{
		return (SipBase *)Sip::buildMessage(this->to_string());
	}
	string SipResponse::to_string()
	{
		string result = "SIP/2.0 " + std::to_string(imethod) + " " + method + "\r\n";
		result += Sip::to_string();
		return result;
	}
	bool SipResponse::isRequest()
	{
		return false;
	}
}
