#include "Options.h"

namespace sip {
	Options::Options(string suri, string sheader, string sbody)
		:Request(suri, sheader, sbody)
	{
		method = "OPTIONS";
	}
}

