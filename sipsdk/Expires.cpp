#include "Expires.h"


namespace sip {
	Expires::Expires(int t)
	{
		tiempo = t;
	}


	Expires::~Expires()
	{
	}

	string Expires::to_string()
	{
		string result = constHeader::expiresHeader + constHeader::kvoperator;
		result += tiempo;
		result += da;
		return result;
	}
}