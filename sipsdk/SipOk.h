#pragma once
#include "SipResponse.h"
#include "Request.h"
namespace sip {
	class SipOk :
		public SipResponse
	{
	public:
		SipOk(string h);
		SipOk(Request * req);
	};
}

