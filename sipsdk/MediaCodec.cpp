#include "MediaCodec.h"


namespace sip {
	MediaCodec::MediaCodec(string value)
	{
		//rtpmap:0 PCMU/8000/1
		size_t pos = value.find_first_of(" ");
		codec = std::atoi(value.substr(0, pos).c_str());

		size_t pos1 = value.find("/", pos+1);
		scodec = value.substr(pos + 1, pos1 - pos - 1);
		size_t pos2 = value.find("/", pos1 + 1);
		if (pos2 != string::npos)
		{
			freq = std::atoi(value.substr(pos1 + 1, pos2 - pos1 - 1).c_str());
			enc = std::atoi(value.substr(pos2 + 1, value.length() - pos2 - 1).c_str());
		}
		else
		{
			freq = std::atoi(value.substr(pos1 + 1, value.length() - pos1 - 1).c_str());
			enc = -1;//no encoding parameter
		}
	}


	MediaCodec::~MediaCodec()
	{
	}

	string MediaCodec::to_string()
	{
		string result = "a=rtpmap:" + std::to_string(codec) + " " + scodec + "/" + std::to_string(freq);
		if(enc>=0)
			result += "/" + std::to_string(enc);
		return result;
	}
}