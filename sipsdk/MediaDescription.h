#pragma once
#include "sipsdk.h"
#include "SipString.h"

#include <string>
#include <list>
using namespace std;

namespace sip {
	class SIPSDK MediaDescription :
		public SipString
	{	
		//RFC 4566
		string media;//audio, video, text, application, message
		int port;
		string protocol;
		string codecs;
		list<SipString *>header;

		std::list<SipString *> split(const string & text);
		SipString *buildHeaders(string name, string content);
		SipString *checkAttributes(string & value);
		SipString *buildCodecs(string & value);
	public:
		MediaDescription(string content);
		~MediaDescription();

		virtual string to_string();
	};
};
