#pragma once
#include "Sip.h"
namespace sip {
	class SIPSDK ContentLength : public SipString
	{
		int content;//largo del sdp
	public:
		ContentLength(int c);
		~ContentLength();
		string to_string();
	};
}

