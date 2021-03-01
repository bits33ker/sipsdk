#include "MediaDescription.h"
#include "SessionDescription.h"
#include "MediaAttribute.h"
#include "MediaCodec.h"
#include "SdpHeader.h"

namespace sip {
	MediaDescription::MediaDescription(string content)
	{
		//m=<media> <port> <proto> <fmt> ...
		size_t pos = content.find_first_of(da);
		string mline = content.substr(0, pos);

		size_t pos1 = mline.find(constSdp::kvoperator);
		size_t pos2 = mline.find(" ");
		media = mline.substr(pos1 + 1, pos2 - pos1 - 1);
		pos1 = pos2;

		pos2 = mline.find(" ", pos1 + 1);
		string p = mline.substr(pos1 + 1, pos2 - pos1 - 1);
		port = std::atoi(p.c_str());
		pos1 = pos2;

		pos2 = mline.find(" ", pos1 + 1);
		protocol = mline.substr(pos1 + 1, pos2 - pos1 - 1);
		pos1 = pos2;

		codecs = mline.substr(pos1 + 1, mline.length() - pos1 - 1);

		//attributes a
		string sheader = content.substr(pos + 2, content.length() - pos - 2);
		header = split(sheader);
	}


	MediaDescription::~MediaDescription()
	{
		header.clear();
	}

	string MediaDescription::to_string()
	{
		string result = constSdp::sdpMedia + constSdp::kvoperator + media
			+ " " + std::to_string(port) + " " + protocol + " "  + codecs + da;
		list<SipString *>::iterator i = header.begin();
		while (i != header.end())
		{
			result += (*i)->to_string() + da;
			i++;
		}
		return result;
	}

	std::list<SipString *> MediaDescription::split(const string & text)
	{
		std::list<SipString *> results;

		// Split into key value pairs separated by '&'.
		size_t prev_amp_index = 0;
		while (prev_amp_index != string::npos)
		{
			size_t amp_index = text.find_first_of(da, prev_amp_index);
			//if (amp_index == string::npos) amp_index = text.find_first_of(_XPLATSTR(';'), prev_amp_index);

			string key_value_pair = text.substr(
				prev_amp_index,
				amp_index == string::npos ? text.size() - prev_amp_index : amp_index - prev_amp_index);
			prev_amp_index = amp_index == string::npos ? string::npos : amp_index + 1;

			size_t equals_index = key_value_pair.find_first_of(constSdp::kvoperator);
			if (equals_index == string::npos)
			{
				continue;
			}
			else if (equals_index == 0)
			{
				string value(key_value_pair.begin() + equals_index + 1, key_value_pair.end());
				results.insert(results.end(), new SdpHeader("", value));
			}
			else
			{
				string value(key_value_pair.begin() + equals_index + constSdp::kvoperator.length(), key_value_pair.end());
				string key(key_value_pair.begin(), key_value_pair.begin() + equals_index);
				if (value.find_first_of(':') != string::npos)
				{
					if(key==constSdp::sdpMediaAttr)
						results.insert(results.end(), buildCodecs(value));
					else
						results.insert(results.end(), buildHeaders(key, value));
				}
				else
				{
					if(value.find(' ') != string::npos)
						results.insert(results.end(), buildHeaders(key, value));
					else
						results.insert(results.end(), checkAttributes(value));
				}
			}
		}

		return results;
	}
	SipString * MediaDescription::buildCodecs(string & value)
	{
		size_t pos = value.find(":");
		string param = value.substr(0, pos);
		string v = value.substr(pos + 1, value.length() - pos - 1);
		if (param != "rtpmap") return new SdpHeader("a", value);//dtmf telephone
		return new MediaCodec(v);
	}
	void MediaDescription::selectCodec(int c)
	{
		codecs = ::to_string(c);
		list<SipString *>::iterator it = header.begin();
		while (it != header.end())
		{
			if (dynamic_cast<MediaCodec *>(*it) != NULL)
			{
				MediaCodec * codec = (MediaCodec *)*it++;
				if (codec->getCodec() != c)
				{
					header.remove(codec);
				}
			}
			else
				it++;
		}
	}
	SipString * MediaDescription::checkAttributes(string & value)
	{
		return new MediaAttribute(value);
	}
	SipString *MediaDescription::buildHeaders(string name, string content)
	{
		return new SdpHeader(name, content);
	}
}