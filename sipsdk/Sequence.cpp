#include "Sequence.h"


namespace sip {
	Sequence::Sequence(string m)
	{//CSeq: 1 INVITE
		int pos = m.find_last_of(" ");
		method = m.substr(pos+1, m.length() - pos);
		seq = std::atoi(m.substr(0, pos).c_str());
	}


	Sequence::~Sequence()
	{
	}

	string Sequence::to_string()
	{
		string result = constHeader::seqHeader + constHeader::kvoperator;
		result += std::to_string(seq);
		result += " " + method;

		return result;
	}
}