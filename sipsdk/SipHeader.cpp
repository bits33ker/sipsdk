#include "SipHeader.h"


namespace sip {
	SipHeader::SipHeader(string name, string h)
	{
		this->name = name;
		header = h;
	}


	SipHeader::~SipHeader()
	{
	}
	string SipHeader::operator=(string s)
	{
		size_t pos = s.find(constHeader::kvoperator);
		if (pos == string::npos)
			throw SipException("ERROR. Cant parse " + s);
		size_t l = constHeader::kvoperator.length();
		name = s.substr(0, pos);
		header = s.substr(pos + l, s.length() - pos - l);
		return s;
	}
}