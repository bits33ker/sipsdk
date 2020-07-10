#include "MediaAttribute.h"


namespace sip {
	MediaAttribute::MediaAttribute(string value)
	{
		if (value == "sendrecv")attr = SendRecvAttr::sendrecv;
		if (value == "sendonly")attr = SendRecvAttr::sendonly;
		if (value == "recvonly")attr = SendRecvAttr::recvonly;
		if (value == "inactive")attr = SendRecvAttr::inactive;
	}

	MediaAttribute::~MediaAttribute()
	{
	}

	string MediaAttribute::to_string()
	{
		string result = "a=";
		switch (attr)
		{
		case SendRecvAttr::inactive:
			result += "inactive";
			break;
		case SendRecvAttr::recvonly:
			result += "recvonly";
			break;
		case SendRecvAttr::sendonly:
			result += "sendonly";
			break;
		case SendRecvAttr::sendrecv:
		default:
			result += "sendrecv";
		}
		return result;
	}
}