#include "SipUri.h"
#include "To.h"


namespace sip {
	To::To(string name, string t)
	{
		this->name = name;
		uri = new SipUri();
		operator=(t);
	}


	To::~To()
	{
		headers.clear();
		delete uri;
	}

	string To::to_string()
	{
		//setlocale(LC_CTYPE, "");

		string result = name + constHeader::kvoperator + "<" + uri->to_string() + ">";

		vector<string>::iterator v = headers.begin();
		while (v != headers.end())
		{
			result += ";" + *v;
			v++;
		}

		return result;
	}
	string To::operator=(string t)
	{
		//To: <sip:8036@192.168.41.245>
		headers.clear();
		int pos = t.find_first_of("<");
		if (pos >= 0)
		{
			*uri = t.substr(pos + 1, t.find_last_of(">") - pos - 1);
		}
		else
			throw SipException("ERROR: " + t);

		pos = t.find(";", t.find_last_of(">"));
		size_t ant = pos;
		if (pos > 0)
		{
			while (pos > 0)
			{
				pos = t.find(";", ant + 1);
				if (pos > 0)
				{
					headers.insert(headers.end(), t.substr(ant + 1, pos - ant));
					ant = pos;
				}
				else
					headers.insert(headers.end(), t.substr(ant + 1, t.length() - ant));
			}

		}
		return t;
	}
}