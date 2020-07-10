#pragma once
#include <string>
#include "Sip.h"

using namespace std;

namespace sip {
	class SIPSDK Expires : public SipString
	{
		int tiempo;//en seg.
	public:
		Expires(int t);
		~Expires();

		virtual string to_string();
	};
};

