#pragma once
#include "SipString.h"
#include "Uri.h"
#include "SipException.h"
#include "HeaderContact.h"

#include <vector>

using namespace std;

namespace sip {
	class SIPSDK To :
		public HeaderContact
	{
		string name;
		Uri *uri;
		vector<string> headers;
	public:
		To(string name, string t);
		~To();

		virtual string to_string();
		virtual string operator=(string t)throw(SipException);
		virtual Uri * getSipUri() { return uri; };
		virtual void add(string h) { headers.insert(headers.end(), h); };
	};
};
