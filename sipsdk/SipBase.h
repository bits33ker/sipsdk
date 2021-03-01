#pragma once
#include "Uri.h"
#include "HeaderContact.h"
#include "SipHeader.h"
#include "Via.h"

#include <memory>
using namespace std;
namespace sip {
	/*
	SipBase: basic info for SipRequest and SipResponse
	*/
	class SipBase {
	public:
		//virtual string getMethod() = 0;
		virtual bool isRequest() = 0;
		virtual HeaderContact * getFrom() = 0;
		virtual HeaderContact * getTo() = 0;
		virtual Via * getVia() = 0;
		virtual SipString * getHeader(string c) = 0;
		//virtual SipBase * clone() = 0;
	};
};