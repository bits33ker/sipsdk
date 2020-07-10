#include "Bye.h"
#include "SipUri.h"


namespace sip {
	Bye::Bye(string suri, string sheader, string sbody)
		:Request(suri, sheader, sbody)
	{
		method = "BYE";
	}

}