#include "Subscribe.h"

namespace sip {
	Subscribe::Subscribe(string suri, string sheader, string sbody)
		:Request(suri, sheader, sbody)
	{
		method = "SUBSCRIBE";
	}
}
