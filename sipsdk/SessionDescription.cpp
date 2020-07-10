#include "Sip.h"
#include "SessionDescription.h"
#include "SdpHeader.h"
#include "SdpVersion.h"
#include "SdpOrigin.h"
#include "SdpConnection.h"
#include "MediaDescription.h"


namespace sip {
	SessionDescription::SessionDescription(string sdp)
	{
		//split media from sdp 
		size_t pos = sdp.find("m=");
		string sline = sdp.substr(0, pos);

		string smedia = sdp.substr(pos, sdp.length() - pos);
		header=split(sline);
		header[constSdp::sdpMedia] = new MediaDescription(smedia);
	}


	SessionDescription::~SessionDescription()
	{
	}

	std::map<string, SipString *> SessionDescription::split(const string & text)
	{
		std::map<string, SipString *> results;

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
				results[string{}] = new SdpHeader("", value);
			}
			else
			{
				string key(key_value_pair.begin(), key_value_pair.begin() + equals_index);
				string value(key_value_pair.begin() + equals_index + constSdp::kvoperator.length(), key_value_pair.end());
				results[key] = buildHeaders(key, value);
			}
		}

		return results;
	}
	SipString *SessionDescription::buildHeaders(string name, string content)
	{
		if (name == constSdp::sdpVersion) return new SdpVersion(content);
		if (name == constSdp::sdpOrigin) return new SdpOrigin(content);
		if (name == constSdp::sdpConnection) return new SdpConnection(content);
		return new SdpHeader(name, content);
	}
	string SessionDescription::optionalHeader(string hdr)
	{
		SipString *base = header[hdr];
		if (base != NULL) return base->to_string() + da;
		return "";
	}
	string SessionDescription::to_string()
	{
		string result = "";
		result += header[constSdp::sdpVersion]->to_string() + da;
		result += header[constSdp::sdpOrigin]->to_string() + da;
		result += header[constSdp::sdpSession]->to_string() + da;
		result += header[constSdp::sdpConnection]->to_string() + da;
		result += header[constSdp::sdpTime]->to_string() + da;
		result += header[constSdp::sdpMedia]->to_string();

		return result;
	}
}