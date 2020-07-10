#include "UserAgent.h"


namespace sip {
	UserAgent::UserAgent(string u)
	{
		user = u;
	}


	UserAgent::~UserAgent()
	{
	}

	string UserAgent::to_string() {
		string result = constHeader::uaHeader + constHeader::kvoperator + user + da;
		return result;
	}
}
