#pragma once
#include "SipResponse.h"
#include "Request.h"
namespace sip {
	class SipTry :
		public SipResponse
	{
	public:
		SipTry(string h);
		SipTry(Request * req);
	};
};
