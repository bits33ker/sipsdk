#include "Register.h"
#include "SipUri.h"


namespace sip {
	Register::Register(string suri, string sheader, string sbody)
		:Request(suri, sheader, sbody)
	{
		//voy comparando linea a linea
		method = "REGISTER";
	}
}