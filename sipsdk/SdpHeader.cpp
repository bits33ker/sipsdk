#include "Sip.h"
#include "SdpHeader.h"
#include "SessionDescription.h"


namespace sip {
	SdpHeader::SdpHeader(string name, string val)
	{
		this->name = name;
		this->value = val;
	}


	SdpHeader::~SdpHeader()
	{
	}

	string SdpHeader::to_string()
	{
		string result = name + constSdp::kvoperator + value;
		return result;
	}
}