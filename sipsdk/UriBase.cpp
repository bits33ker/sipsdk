#include "UriBase.h"


namespace sip {
	UriBase::UriBase(string u)
	{
		operator=(u);
	}


	UriBase::~UriBase()
	{
	}

	string UriBase::to_string()
	{
		string u = ip;

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
	string UriBase::operator=(string u)
	{
		//192.168.41.230:11121;rport;branch=z9hG4bKddsEurK4164f00.sa12088ptb7Rm
		headers.clear();
		port = -1;

		int pos = u.find_first_of(";");

		string address = u.substr(0, pos);
		size_t ant = pos;
		if (pos > 0)
		{
			while (pos > 0)
			{
				pos = u.find(";", ant + 1);
				if (pos > 0)
				{
					headers.insert(headers.end(), u.substr(ant + 1, pos - ant - 1));
					ant = pos;
				}
				else
					headers.insert(headers.end(), u.substr(ant + 1, u.length() - ant));
			}

		}

		int pos2 = address.find_first_of(":");

		if (pos2 > 0)
			{
				ip = address.substr(0, pos2);
				port = std::atoi(address.substr(pos2 + 1, address.length() - pos2).c_str());
			}
			else
				ip = address;
		return u;
	}
}