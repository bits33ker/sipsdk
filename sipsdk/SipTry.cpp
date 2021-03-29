#include "SipTry.h"
#include "To.h"
#include "ContentLength.h"
#include <cstdlib>
using namespace std;
namespace sip {
	SipTry::SipTry(string h)
		:SipResponse(100, "Trying", h, "")
	{

	}
	SipTry::SipTry(Request *req)
		: SipResponse(100, "Trying", "", "")
	{
		header[constHeader::viaHeader] = buildHeaders(constHeader::viaHeader, req->getHeader(constHeader::viaHeader)->to_string());
		header[constHeader::fromHeader] = buildHeaders(constHeader::viaHeader, req->getHeader(constHeader::fromHeader)->to_string());
		To * to= (To *)buildHeaders(constHeader::toHeader, req->getHeader(constHeader::toHeader)->to_string());;
		string tag = "tag=";
		tag = tag + ::to_string(rand());
		to->add(tag);
		header[constHeader::toHeader] = to;
		header[constHeader::callidHeader] = buildHeaders(constHeader::callidHeader, req->getHeader(constHeader::callidHeader)->to_string());
		header[constHeader::seqHeader] = buildHeaders(constHeader::seqHeader, req->getHeader(constHeader::seqHeader)->to_string());
		header[constHeader::lenHeader] = new ContentLength(0);
	}
}