#pragma once
#include <exception>
#include <string>
using namespace std;
namespace sip {
	class SipException :
		public exception
	{
		string msg;
	public:
		SipException(string a) { msg = a; };
		~SipException() {};

		string get_message() { return msg; };


	};
};
