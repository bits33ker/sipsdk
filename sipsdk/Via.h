#pragma once
#include "sipsdk.h"
#include "Uri.h"
#include "SipException.h"
#include <vector>

using namespace std;

namespace sip {
	namespace cVia {
		const string viaUdp = "UDP";
		const string viaTcp = "TCP";
		const string viaTls = "TLS";
	}
	class SIPSDK Via :
		public SipString
	{
		string transport;//UDP, TCP, TLS
		Uri *uri;
		//vector<string> headers;
	public:
		Via(string v);
		~Via();
		virtual string to_string();
		string operator=(string v);

		Uri * getUri() { return uri; };
	};
};

