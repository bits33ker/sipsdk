#include "Invite.h"
#include "SipUri.h"
#include "SipException.h"
namespace sip{
	Invite::Invite(string suri, string sheader, string sbody)
		:Request(suri, sheader, sbody)
	{
		method = "INVITE";
	}
}
