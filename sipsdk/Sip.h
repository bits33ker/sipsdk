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
	
	class SIPSDK SipRequest;

	class SIPSDK Sip : public SipBase, SipString
	{
		//string sline;//request o status
		std::map<string, string> Sip::split(const string & text, const string kvoperator);
		std::map<string, SipString *> splitHeader(const string & text);
		string header_compose(string arg);
		//string body_compose(string arg);
		SipString *buildHeaders(string name, string content);
		string optionalHeader(string hdr);

	protected:
		map<string, SipString *> header;
		//map<string, string> body;
		list<SessionDescription *>sdps;

	public:
		Sip(string sheader, string sbody);
		~Sip();

		static Sip * buildMessage(string text)throw(SipException);
		SipRequest *buildRequest();
		virtual string to_string();

		virtual HeaderContact* getFrom();
		virtual HeaderContact * getTo();
		virtual Via * getVia();
		virtual SipString * getHeader(string c);
	};
};
#endif