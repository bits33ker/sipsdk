#pragma once
#include "Sip.h"
#include "SipException.h"
#include "Uri.h"

using namespace std;

namespace sip {
	class SIPSDK HeaderContact :
		public SipString
	{

	public:
		string operator=(string f)throw(SipException);
		virtual Uri *getSipUri() = 0;
		virtual void add(string h) = 0;
	};
};

