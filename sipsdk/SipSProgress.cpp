#include "SipSProgress.h"
#include "To.h"
#include "ContentLength.h"
#include "MediaDescription.h"
#include <cstdlib>
using namespace std;
namespace sip {
	SipSProgress::SipSProgress(string h)
		:SipResponse(200, "OK", h, "")
	{

	}
	SipSProgress::SipSProgress(Request *req)
		: SipResponse(183, "Session Progress", req->to_string(), req->getSessionDescription())
	{
		To * to = (To *)getHeader(constHeader::toHeader);
		string tag = "tag=";
		tag = tag + ::to_string(rand());
		to->add(tag);
		if (sdps.size())
		{
			SessionDescription *sdp = *sdps.begin();
			string codecs= ((MediaDescription *)sdp->getMedia())->getCodecs();
			//select the first one
			int c = std::atoi(codecs.substr(0, codecs.find_first_of(' ')).c_str());
			((MediaDescription *)sdp->getMedia())->selectCodec(c);
		}

		//select codec
	}

}
