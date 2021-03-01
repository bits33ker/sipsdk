#ifndef SIP_H_
#define SIP_H_

#include <string>
#include <list>
#include <map>
#include <memory>
#include "SipBase.h"
#include "SipString.h"
#include "SipRequest.h"
#include "SipHeader.h"
#include "SessionDescription.h"
#include "sipsdk.h"
using namespace std;
namespace sip{
	namespace methods {
		const string INVITE = "INVITE";
		const string REGISTER = "REGISTER";
		const string BYE = "BYE";
		const string OPTIONS = "OPTIONS";
		const string SUBSCRIBE = "SUBSCRIBE";
		const string ACK = "ACK";
	};

	class SIPSDK SipRequest;

	class SIPSDK Sip : public SipBase, SipString
	{
		//string sline;//request o status
		std::map<string, string> split(string & text, const string kvoperator);
		std::map<string, SipString *> splitHeader(const string & text);
		string header_compose(string arg);
		//string body_compose(string arg);
		string optionalHeader(string hdr);
		string mustHeader(string hdr);

	protected:
		map<string, SipString *> header;
		//map<string, string> body;
		list<SessionDescription *>sdps;

	public:
		Sip(string sheader, string sbody);
		~Sip();

		static Sip * buildMessage(string text);
		static SipString *buildHeaders(string name, string content);
		SipRequest *buildRequest();
		virtual string to_string();

		virtual HeaderContact* getFrom();
		virtual HeaderContact * getTo();
		virtual Via * getVia();
		virtual SipString * getHeader(string c);
		string getSessionDescription();
	};
};
#endif