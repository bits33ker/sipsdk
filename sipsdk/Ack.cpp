#include "Ack.h"
#include "SipUri.h"
#include "SipException.h"
namespace sip {
	Ack::Ack(string suri, string sheader, string sbody)
		:Request(suri, sheader, sbody)
	{
		method = "ACK";
	}
}
