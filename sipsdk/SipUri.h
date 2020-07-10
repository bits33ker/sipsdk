#ifndef SIPURI_H_
#define SIPURI_H_
#include "Sip.h"
#include "Uri.h"
#include <string>
#include <vector>

using namespace std;
#ifndef SIPSDK
#ifdef SIPSDK_EXPORTS
#define SIPSDK __declspec(dllexport)
#else
#define SIPSDK __declspec(dllimport)
#endif
#endif

namespace sip {
	class SipUri : public Uri
	{
		string user;
		string ip;
		int port;//5060 default

		vector<string> headers;
	public:
		const string huri = "sip:";

		SipUri() {};
		SipUri(string u);
		SipUri(SipUri &u);
		~SipUri();

		SipUri operator=(SipUri u);
		string operator=(string u);

		string to_string();
		void setUser(string u) { user = u; };
		string getUser() { return user; };
		void setIp(string i) { ip = i; };
		string getIp() { return ip; };
		void setPort(int p) { port = p; };
		int getPort() { return port; };
	};
}
#endif