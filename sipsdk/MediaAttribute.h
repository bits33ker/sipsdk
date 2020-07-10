#pragma once
#include "sipsdk.h"
#include "SipString.h"

#include <string>
using namespace std;

namespace sip {
	enum SendRecvAttr {
		recvonly = 0,
		sendrecv,
		sendonly,
		inactive //for conference
	};
	class MediaAttribute :
		public SipString
	{
		int attr;
	public:
		MediaAttribute(string value);
		~MediaAttribute();

		virtual string to_string();
	};
};
