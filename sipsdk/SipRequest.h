#pragma once
#include "sipsdk.h"
#include "Uri.h"
#include "SipBase.h"

#include <string>
#include <memory>
using namespace std;

namespace sip {
	class SIPSDK SipRequest :
		public SipBase, public SipString
	{
	public:
		virtual string getMethod() = 0;
		virtual Uri * getSipUri() = 0;
		virtual int getMaxForwards() = 0;
	};
};
