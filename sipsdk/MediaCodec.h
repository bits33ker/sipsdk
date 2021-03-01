#pragma once
#include "sipsdk.h"
#include "SipString.h"
namespace sip {
	class SIPSDK MediaCodec :
		public SipString
	{
		int codec;
		int freq;
		int enc;//enconding parameter

		string scodec;
	public:
		MediaCodec(string value);
		~MediaCodec();

		virtual string to_string();
		int getCodec() { return codec; };
	};
};
