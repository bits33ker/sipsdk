#include "ContentLength.h"


namespace sip {
	ContentLength::ContentLength(int c)
	{
		content = c;
	}


	ContentLength::~ContentLength()
	{
	}

	string ContentLength::to_string()
	{
		string result = constHeader::lenHeader + constHeader::kvoperator;
		result += content;
		result += da;
		return result;
	}
}