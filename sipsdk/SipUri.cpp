#include "SipUri.h"
#include "SipException.h"


namespace sip {
	SipUri::SipUri(string u)
	{
		operator=(u);
	}
	string SipUri::operator=(string u)
	{
		headers.clear();
		int luri = huri.length();
		port = -1;//default 5060

		int pos = u.find(huri);
		if (pos != 0)
			throw SipException("ERROR: " + u);

		int pos2 = u.find_first_of("@");
		if (pos2 > 0)
		{
			user = u.substr(luri, pos2 - luri);
			pos = pos2;
		}
		else
			pos = luri - 1;

		string address = u.substr(pos + 1, u.length() - pos - 1);
		pos = address.find_first_of(";");
		size_t ant = pos;
		if (pos > 0)
		{
			while (pos > 0)
			{
				pos = address.find(";", ant + 1);
				if (pos > 0)
				{
					headers.insert(headers.end(), address.substr(ant + 1, pos - ant));
					ant = pos;
				}
				else
					headers.insert(headers.end(), address.substr(ant + 1, address.length() - ant));
			}

		}

		pos2 = address.find_first_of(":");
		if (pos < 0)//no tag
		{
			if (pos2 > 0)
			{
				ip = address.substr(0, pos2);
				port = std::atoi(address.substr(pos2 + 1, address.length() - pos2).c_str());
			}
			else
				ip = address;
		}
		else
		{
			if (pos2 > 0)
			{
				ip = address.substr(0, pos2);
				port = std::atoi(address.substr(pos2 + 1, pos - pos2).c_str());
			}
			else
			{
				ip = address.substr(0, pos2);
			}
		}
		return u;
	}
	SipUri::SipUri(SipUri & u)
	{
		this->operator=(u);
	}

	SipUri::~SipUri()
	{
		headers.clear();
	}

	string SipUri::to_string()
	{
		string u = huri;
		if (!user.empty())
			u = u + user + "@";
		u += ip;
		if (port != -1)
			u = u + ":" + std::to_string(port);

		vector<string>::iterator v = headers.begin();
		while (v != headers.end())
		{
			u += ";" + *v;
			v++;
		}
		return u;
	}
	SipUri SipUri::operator=(SipUri u)
	{
		this->user = u.getUser();
		this->port = u.getPort();
		this->ip = u.getIp();
		//this->tag = u.getTag();
		return *this;
	}

}
