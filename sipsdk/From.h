#pragma once
#include "sip.h"
#include "Uri.h"
#include "SipException.h"
#include "HeaderContact.h"

#include <vector>

using namespace std;

namespace sip {
	class SIPSDK From :
		public HeaderContact
	{
		Uri *uri;
		string key;
		string name;
		vector<string> headers;

	public:
		From(string n, string f);
		~From();

		virtual string to_string();
		virtual string operator=(string f)throw(SipException);
		virtual Uri *getSipUri() { return uri; };
		virtual void add(string h) { headers.insert(headers.end(), h); };
	};
};

