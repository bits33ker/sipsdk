#pragma once
#include "SipString.h"
namespace sip {
	class SdpHeader :
		public SipString
	{
		string name;
		string value;
	public:
		SdpHeader(string name, string val);
		~SdpHeader();

		virtual string to_string();
	};
};