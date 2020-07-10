#include "Forwards.h"


namespace sip {
	Forwards::Forwards(int f)
	{
		maxforwards = f;
	}


	Forwards::~Forwards()
	{
	} 
	string Forwards::to_string()
	{
		string result = constHeader::forwardsHeader + constHeader::kvoperator;
		result += maxforwards;
		result += da;
		return result;
	}
}
