#include "Request.h"
#include "SipUri.h"
#include "SipResponse.h"
#include "SipTry.h"
#include "SipOk.h"
#include "SipSProgress.h"

namespace sip {
	Request::Request(string suri, string sheader, string sbody)
		:Sip(sheader, sbody)
	{
		uri = new SipUri(suri);
		//voy comparando linea a linea
	}
	Request::~Request()
	{
		delete uri;
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
	bool Request::isRequest()
	{
		return true;
	}
	SipBase * Request::buildResponse(int imethod, string method)
	{
		if (imethod == 100)return new SipTry(this);
		if (imethod == 200)return new SipOk(this);
		if (imethod == 183)return new SipSProgress(this);
		return new SipResponse(imethod, method, ((Sip *)this)->to_string(), "");
	}


}