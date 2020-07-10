#pragma once
#include <string>

using namespace std;
namespace sip {
	const string da = "\r\n";
	const string da2 = "\r\n\r\n";

	class SipString
	{
	public:
		virtual string to_string()=0;
	};
};

