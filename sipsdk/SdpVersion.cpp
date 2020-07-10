#include "SdpVersion.h"
#include "SessionDescription.h"

namespace sip {
	SdpVersion::SdpVersion(string content)
	{
		version = std::atoi(content.c_str());
	}

	SdpVersion::~SdpVersion()
	{
	}

	string SdpVersion::to_string()
	{
		return constSdp::sdpVersion + constSdp::kvoperator + std::to_string(version);
	}
}