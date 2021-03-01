#include "From.h"
#include "SipUri.h"
#include "SipException.h"


namespace sip {
	From::From(string n, string f)
	{
		key = n;
		uri = new SipUri();
		operator=(f);
	}


	From::~From()
	{
		headers.clear();
		delete uri;
	}

	string From::to_string()
	{
		//setlocale(LC_CTYPE, "");

		string result = key + ": ";
		if (!name.empty())
			result += "\"" + name + "\" ";
		result += "<" + uri->to_string() + ">";

		vector<string>::iterator v = headers.begin();
		while (v != headers.end())
		{
			result += ";" + *v;
			v++;
		}

		return result;

	}
	string From::operator=(string f)
	{
		//From: "John Doe" <sip:5409@192.168.41.230>;tag=296737002
		headers.clear();
		int pos = f.find_first_of("<");
		if (pos<0)
			throw SipException("ERROR " + f);

		if (pos > 0)
		{
			string t = f.substr(0, pos);
			int q = t.find_first_of("\"");
			if (q >= 0)
			{
				name = t.substr(q + 1, t.find_last_of("\"") - q - 1);
			}
		}
		*uri = f.substr(pos + 1, f.find_last_of(">") - pos - 1);
		
		pos = f.find_first_of(";");
		size_t ant = pos;
		if (pos > 0)
		{
			while (pos > 0)
			{
				pos = f.find(";", ant + 1);
				if (pos > 0)
				{
					headers.insert(headers.end(), f.substr(ant + 1, pos - ant));
					ant = pos;
				}
				else
					headers.insert(headers.end(), f.substr(ant + 1, f.length() - ant));
			}

		}
		return f;
	}
}