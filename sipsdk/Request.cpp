#include "Request.h"
#include "SipUri.h"


namespace sip {
	Request::Request(string suri, string sheader, string sbody)
		:Sip(sheader, sbody)
	{
		uri = unique_ptr<Uri>(new SipUri(suri));
		//voy comparando linea a linea
	}

	string Request::to_string()
	{
		return getMethod() + " " + uri->to_string() + " SIP/2.0" + da + Sip::to_string();
	}
	int Request::getMaxForwards()
	{
		return std::atoi(header[constHeader::forwardsHeader]->to_string().c_str());
	}
	Sip *Request::clone()
	{
		return Sip::buildMessage(this->to_string());
	}

}