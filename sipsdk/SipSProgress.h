#pragma once
#include "SipResponse.h"
#include "Request.h"
namespace sip {
	class SipSProgress :
		public SipResponse
	{
	public:
		SipSProgress(string h);
		SipSProgress(Request * req);
	};
}

