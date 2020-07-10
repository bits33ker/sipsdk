#pragma once
#include "sipsdk.h"
#include "Sip.h"
#include <string>
using namespace std;

namespace sip {
	namespace constHeader {
		const string viaHeader = "Via";
		const string fromHeader = "From";
		const string toHeader = "To";
		const string forwardsHeader = "Max-Forwards";
		const string expiresHeader = "Expires";
		const string allowHeader = "Allow";
		const string callidHeader = "Call-ID";
		const string seqHeader = "CSeq";
		const string contactHeader = "Contact";
		const string uaHeader = "User-Agent";
		const string authHeader = "Authorization";
		const string serverHeader = "Server";
		const string earlymediaHeader = "P-Early-Media";
		const string identHeader = "P-Asserted-Identity";
		const string acceptHeader = "Accept";
		const string reasonHeader = "Reason";
		const string evHeader = "Event";
		const string suppHeader = "Supported";
		const string allowEvHeader = "Allow-Events";
		const string lenHeader = "Content-Length";
		const string typeHeader = "Content-Type";
		const string kvoperator = ": ";
	};

	class SIPSDK SipHeader :
		public SipString
	{
		//Call-ID: 82814277-1@192.168.41.230
		//Max-Forwards: 70
		//User-Agent: MitE1xv4.4.5.973
		//Expires: 300
		string name;
		string header;
	public:
		SipHeader() {};
		SipHeader(string name, string h);
		~SipHeader();
		string operator=(string s) throw(SipException);
		virtual string to_string() { return name + constHeader::kvoperator + header; };
	};

}