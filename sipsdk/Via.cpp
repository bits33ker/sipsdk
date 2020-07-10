#include "Via.h"
#include "UriBase.h"


namespace sip {
	Via::Via(string v)
	{
		operator=(v);
	}

	Via::~Via()
	{
		delete uri;
	}
	string Via::to_string()
	{

		//setlocale(LC_CTYPE, "");

		string result = "Via: SIP/2.0";
		if (!transport.empty())
			result += "/" + transport;
		result += " " + uri->to_string();

		return result;
	}
	string Via::operator=(string v)throw(SipException)
	{
		//Via: SIP/2.0/UDP 192.168.41.230:11121;rport;branch=z9hG4bKddsEurK4164f00.sa12088ptb7Rm
		size_t pos = v.find_last_of(" ");
		if (pos < 0)
			throw SipException("ERROR " + v);
		
		string t = v.substr(0, pos);
		if ((int)t.find(cVia::viaUdp)>=0) transport = cVia::viaUdp;
		if ((int)t.find(cVia::viaTcp)>=0) transport = cVia::viaTcp;
		if ((int)t.find(cVia::viaTls)>=0) transport = cVia::viaTls;

		uri = new UriBase(v.substr(pos+1, v.length()-pos-1));

		return v;
	}
}