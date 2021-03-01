#include "Sip.h"
#include "SipResponse.h"
#include "Invite.h"
#include "Bye.h"
#include "Ack.h"
#include "Register.h"
#include "Options.h"
#include "Subscribe.h"
#include "SipHeader.h"
#include "Via.h"
#include "From.h"
#include "To.h"
#include "Sequence.h"

namespace sip {
	Sip * Sip::buildMessage(string text)
	{
		size_t pos = text.find_first_of(da);
		string sline = text.substr(0, pos);

		size_t hpos = text.find(da2, pos+2);

		string sheader = text.substr(pos + 2, hpos - pos - 2);
		string sbody = text.substr(hpos + 4, text.length());

		//sip-request or sip-response
		if (sline.find("SIP") == 0)
		{//sip-response
			size_t offset1 = sline.find(' ');
			size_t offset2 = sline.find_last_of(' ');
			if (offset1 == string::npos || offset2 == string::npos)
				throw SipException("ERROR parsing " + sline);
			int imethod = std::atoi(sline.substr(offset1 + 1, offset2 - offset1 - 1).c_str());
			string method = sline.substr(offset2 + 1, sline.length() - offset2- 1);
			return (Sip *)new SipResponse(imethod, method, sheader, sbody);
		}
		//sip-request
		size_t offset = sline.find_first_of(' ');
		string method = sline.substr(0, offset);
		size_t offset2 = sline.find(' ', offset+1);
		if (offset2 == string::npos)
			offset2 = sline.length();
		string uri = sline.substr(offset + 1, offset2 - offset - 1);
		if (method == methods::INVITE) return (Sip *)new Invite(uri, sheader, sbody);
		if (method == methods::BYE) return (Sip *)new Bye(uri, sheader, sbody);
		if (method == methods::ACK) return (Sip *)new Ack(uri, sheader, sbody);
		if (method == methods::REGISTER) return (Sip *)new Register(uri, sheader, sbody);
		if (method == methods::OPTIONS) return (Sip *)new Options(uri, sheader, sbody);
		if (method == methods::SUBSCRIBE) return (Sip *)new Subscribe(uri, sheader, sbody);

		throw SipException("Exception Method: " + method + " not implemented yet");
	}
	Sip::Sip(string sheader, string sbody)
	{
		header.clear();
		sdps.clear();
		header = splitHeader(sheader);
		if(sbody!="")
			sdps.insert(sdps.end(), new SessionDescription(sbody));
	}
	SipRequest *Sip::buildRequest()
	{
		SipRequest *request = (SipRequest *)new Invite("5409@192.168.40.34", "", "");
		return request;
	}
	std::map<string, string> Sip::split(string & text, const string kvoperator)
	{
		std::map<string, string> results;

		// Split into key value pairs separated by '&'.
		size_t prev_amp_index = 0;
		while (prev_amp_index != string::npos)
		{
			size_t amp_index = text.find_first_of("\r\n", prev_amp_index);
			//if (amp_index == string::npos) amp_index = text.find_first_of(_XPLATSTR(';'), prev_amp_index);

			string key_value_pair = text.substr(
				prev_amp_index,
				amp_index == string::npos ? text.size() - prev_amp_index : amp_index - prev_amp_index);
			prev_amp_index = amp_index == string::npos ? string::npos : amp_index + 1;

			size_t equals_index = key_value_pair.find_first_of(kvoperator);
			if (equals_index == string::npos)
			{
				continue;
			}
			else if (equals_index == 0)
			{
				string value(key_value_pair.begin() + equals_index + 1, key_value_pair.end());
				results[string{}] = value;
			}
			else
			{
				string key(key_value_pair.begin(), key_value_pair.begin() + equals_index);
				string value(key_value_pair.begin() + equals_index + kvoperator.length(), key_value_pair.end());
				//results[key] = value;
				results.insert(pair<string, string>(key, value));
			}
		}

		return results;
	}

	SipString *Sip::buildHeaders(string name, string content)
	{
		if (name == constHeader::viaHeader)return new Via(content);
		if (name == constHeader::fromHeader) return new From(name, content);
		if (name == constHeader::toHeader) return new To(name, content);
		if (name == constHeader::contactHeader) return new To(name, content);
		if (name == constHeader::seqHeader) return new Sequence(content);
		if (name == constHeader::identHeader) return new From(name, content);

		return new SipHeader(name, content);
	}

	std::map<string, SipString *> Sip::splitHeader(const string & text)
	{
		std::map<string, SipString *> results;

		// Split into key value pairs separated by '&'.
		size_t prev_amp_index = 0;
		while (prev_amp_index != string::npos)
		{
			size_t amp_index = text.find_first_of("\r\n", prev_amp_index);
			//if (amp_index == string::npos) amp_index = text.find_first_of(_XPLATSTR(';'), prev_amp_index);

			string key_value_pair = text.substr(
				prev_amp_index,
				amp_index == string::npos ? text.size() - prev_amp_index : amp_index - prev_amp_index);
			prev_amp_index = amp_index == string::npos ? string::npos : amp_index + 1;

			size_t equals_index = key_value_pair.find_first_of(constHeader::kvoperator);
			if (equals_index == string::npos)
			{
				continue;
			}
			else if (equals_index == 0)
			{
				string value(key_value_pair.begin() + equals_index + 1, key_value_pair.end());
				results[string{}] = new SipHeader("", value);
			}
			else
			{
				string key(key_value_pair.begin(), key_value_pair.begin() + equals_index);
				string value(key_value_pair.begin() + equals_index + constHeader::kvoperator.length(), key_value_pair.end());
				//results[key] = buildHeaders(key, value);
				results.insert(pair<string, SipString *>(key, buildHeaders(key, value)));
			}
		}

		return results;
	}

	Sip::~Sip()
	{
		
		while (header.size()) {
			string key = header.begin()->first;
			header.erase(key);
		}
		//body.clear();
		while (sdps.size())
		{
			SessionDescription * sdp = NULL;
			sdp = *sdps.begin();
			sdps.remove(sdp);
			delete sdp;
		}
	}
	string Sip::header_compose(string arg)
	{
		string aux;
		try {
			std::map<string, SipString *>::iterator m = header.find(arg);
			if(m!=header.end())aux = m->second->to_string();
			if (aux.empty())return "";
		}
		catch (...)
		{
			return "";
		}
		string result = arg + constHeader::kvoperator + aux + da;
		return result;
	}
	/*
	string Sip::body_compose(string arg)
	{
		string aux;
		try {
			aux = body.at(arg);
			if (aux.empty())return "";
		}
		catch (...)
		{
			return "";
		}
		string result = arg + "=" + aux + da;
		return result;
	}*/
	string Sip::optionalHeader(string hdr)
	{
		SipString *base = header[hdr];
		if (base != NULL) return base->to_string() + da;
		return "";
	}
	string Sip::mustHeader(string hdr)
	{
		SipString *base = header[hdr];
		if (base != NULL) return base->to_string() + da;
		throw SipException(hdr + "is missing");
	}
	HeaderContact * Sip::getFrom()
	{
		return (HeaderContact *)header[constHeader::fromHeader];
	}
	HeaderContact * Sip::getTo()
	{
		return (HeaderContact *)header[constHeader::toHeader];
	}
	Via * Sip::getVia()
	{
		return (Via *)header[constHeader::viaHeader];
	}
	SipString * Sip::getHeader(string c)
	{
		return header[c];
	}
	string Sip::to_string()
	{
		string result = "";// sline + sip::da;
		result += mustHeader(constHeader::viaHeader);
		result += mustHeader(constHeader::fromHeader);
		result += mustHeader(constHeader::toHeader);
		result += mustHeader(constHeader::callidHeader);
		result += mustHeader(constHeader::seqHeader);
		//optionals from here
		result += optionalHeader(constHeader::contactHeader);
		result += optionalHeader(constHeader::forwardsHeader);
		result += optionalHeader(constHeader::uaHeader);
		result += optionalHeader(constHeader::authHeader);
		result += optionalHeader(constHeader::evHeader);
		result += optionalHeader(constHeader::suppHeader);
		result += optionalHeader(constHeader::acceptHeader);
		result += optionalHeader(constHeader::allowEvHeader);
		result += optionalHeader(constHeader::serverHeader);
		result += optionalHeader(constHeader::expiresHeader);
		result += optionalHeader(constHeader::allowHeader);
		result += optionalHeader(constHeader::earlymediaHeader);
		result += optionalHeader(constHeader::identHeader);
		result += optionalHeader("P-Mitrol-idLlamada");
		result += optionalHeader("P-Mitrol-PerfilRuteo");
		result += optionalHeader(constHeader::reasonHeader);
		result += mustHeader(constHeader::lenHeader);
		result += optionalHeader(constHeader::typeHeader);
		result += da;
		if (sdps.size() > 0)
		{
			list<SessionDescription *>::iterator i = sdps.begin();
			while (i!=sdps.end())
			{
				result += (*i)->to_string();
				i++;
			}
		}

		return result;
	}
	string Sip::getSessionDescription()
	{
		if (!sdps.size()) return "";
		return (*sdps.begin())->to_string();
	}

}