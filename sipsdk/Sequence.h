#pragma once

#include "Sip.h"
#include <string>

using namespace std;

namespace sip {
	class SIPSDK Sequence : public SipString
	{
		int seq;//numero de sequencia del metodo
		string method;//metodo request
	public:
		Sequence() { seq = -1; };
		Sequence(string m);
		~Sequence();

		virtual string to_string();
	};
}

