#pragma once
#include "Sip.h"

namespace sip {
	class SIPSDK Forwards : public SipString
	{
		int maxforwards;
	public:
		Forwards(int f);
		~Forwards();
		virtual string to_string();
	};
};
