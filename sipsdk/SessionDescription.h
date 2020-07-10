#pragma once
#include "sipsdk.h"
#include "SipString.h"
#include <string>
#include <map>
using namespace std;
/*
* RFC 4566
* https://tools.ietf.org/html/rfc4566#page-10
*/
namespace sip {
	namespace constSdp {
		const string sdpVersion = "v";
		const string sdpOrigin = "o";
		const string sdpSession = "s";
		const string sdpConnection = "c";
		const string sdpTime = "t";
		const string sdpMedia = "m";
		const string sdpMediaAttr = "a";
		const string kvoperator = "=";
		const string da = "\r\n";
	};
	class SIPSDK SessionDescription :
		public SipString
	{
		map<string, SipString *> header;

		std::map<string, SipString *> split(const string & text);
		SipString *buildHeaders(string name, string content);
		string optionalHeader(string hdr);
	public:
		SessionDescription(string sdp);
		~SessionDescription();

		virtual string to_string();
	};
};
