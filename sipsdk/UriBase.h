#pragma once
#include "Uri.h"
#include <string>
#include <vector>

using namespace std;

namespace sip {
	class SIPSDK UriBase :
		public Uri
	{
		string ip;
		int port;//5060 default

		vector<string> headers;
	public:

		UriBase() {};
		UriBase(string u);
		~UriBase();

		string operator=(string u);

		string to_string();
		string getIp() { return ip; };
		string getUser() { return ""; };
		int getPort() { return port; };
	};
}