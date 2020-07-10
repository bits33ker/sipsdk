#include "stdafx.h"
#include "CppUnitTest.h"
#include "../sipsdk/Invite.h"
#include "../sipsdk/Bye.h"
#include "../sipsdk/Ack.h"
#include "../sipsdk/Register.h"
#include "../sipsdk/Options.h"
#include "../sipsdk/Subscribe.h"
#include "../sipsdk/SipResponse.h"
#include "../sipsdk/To.h"
#include "../sipsdk/From.h"
#include "../sipsdk/Via.h"
#include "../sipsdk/SipUri.h"
#include "../sipsdk/SessionDescription.h"
#include "../sipsdk/SipException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sip;
using namespace std;

namespace forwardtest
{
	TEST_CLASS(ForwardTest)
	{
		void test(string linea, string result)throw(SipException)
		{
			size_t ar = 0;
			size_t al = 0;
			size_t pr = result.find_first_of(da);
			size_t pl = linea.find_first_of(da);
			while (pr >= 0 && pl >= 0 && pl < linea.length())
			{
				string sr = result.substr(ar, pr - ar);
				string sl = linea.substr(al, pl - ar);
				if (sr != sl)
					throw SipException(sl);

				ar = pr + da.length();
				al = pl + da.length();
				pr = result.find(da, ar);
				pl = linea.find(da, al);
			}
			int c = result.compare(linea);
			if (c != 0)
				throw SipException(linea);

			Assert::AreEqual(result, linea);
		}
	public:
		TEST_METHOD(TestForward)
		{
			string method = "INVITE sip:8036@192.168.41.245 SIP/2.0\r\n";
			string via = "Via: SIP/2.0/UDP 192.168.41.230:11121;rport;branch=z9hG4bKddsEurK4164f00.sa12088ptb7Rm\r\n";
			string from = "From: \"Eugenio Voss\" <sip:5409@192.168.41.230>;tag=296737002\r\n";
			string to = "To: <sip:8036@192.168.41.245>\r\n";
			string callid = "Call-ID: 82814277-1@192.168.41.230\r\n";
			string seq = "CSeq: 1 INVITE\r\n";
			string contact = "Contact: <sip:5409@192.168.41.230:11121;transport=udp>\r\n";
			string forwards = "Max-Forwards: 70\r\n";
			string agent = "User-Agent: MitE1xv4.4.5.973\r\n";
			string expires = "Expires: 300\r\n";
			string allow = "Allow: INVITE, ACK, CANCEL, BYE, REGISTER, SUBSCRIBE, NOTIFY, REFER, OPTIONS, INFO\r\n";
			string early_supp = "P-Early-Media: Supported\r\n";
			string identity = "P-Asserted-Identity: \"Eugenio Voss\" <sip:5409@192.168.41.230>\r\n";
			string idllamada = "P-Mitrol-idLlamada: 180314120413252_MIT_11118\r\n";
			string ruteo = "P-Mitrol-PerfilRuteo: 1\r\n";
			string length = "Content-Length: 381\r\n";
			string type = "Content-Type: application/sdp\r\n\r\n";

			string linea = method + via + from + to + callid + seq + contact + forwards +
				agent + expires + allow + early_supp + identity + idllamada + ruteo +
				length + type;

			string version = "v=0\r\n";
			string owner = "o=5409 0 0 IN IP4 192.168.41.230\r\n";
			string session = "s=MitE1x Call\r\n";
			string connection = "c=IN IP4 192.168.41.230\r\n";
			string tiempo = "t=0 0\r\n";
			string media = "m=audio 35102 RTP/AVP 0 8 4 18 9 97 2 101\r\n";
			string attr = "a=sendrecv\r\n";
			string pcmu = "a=rtpmap:0 PCMU/8000/1\r\n";
			string pcma = "a=rtpmap:8 PCMA/8000/1\r\n";
			string g723 = "a=rtpmap:4 G723/8000/1\r\n";
			string g729 = "a=rtpmap:18 G729/8000/1\r\n";
			string annexb = "a=fmtp:18 annexb=no\r\n";
			string g722 = "a=rtpmap:9 G722/8000/1\r\n";
			string ilbc = "a=rtpmap:97 iLBC/8000/1\r\n";
			string rtpmap = "a=rtpmap:2 2/8000/1\r\n";
			string tel_event = "a=rtpmap:101 telephone-event/8000\r\n";
			string fmtp = "a=fmtp:101 0-15\r\n";

			//linea = linea + version + owner + session + connection + tiempo +
			//	media + attr + pcmu + pcma + g723 + g729 + annexb + g722 +
			//	ilbc + rtpmap + tel_event + fmtp;

			string methodf = "INVITE sip:8036@192.168.41.227 SIP/2.0\r\n";
			string viaf = "Via: SIP/2.0/UDP 192.168.41.245:10002;rport;branch=z9hG4bKddsEurK18523f00.sa23048ptb7Rm\r\n";
			string fromf = "From: \"Eugenio Voss\" <sip:5409@192.168.41.245>;tag=572389300\r\n";
			string tof = "To: <sip: 8036@192.168.41.227>\r\n";
			string callidf = "Call-ID: 205684380-0@192.168.41.245\r\n";
			string seqf = "CSeq: 1 INVITE\r\n";
			string contactf = "Contact: <sip:5409@192.168.41.245:10002;transport=udp>\r\n";
			string forwardf = "Max-Forwards: 69\r\n";
			string agentf = "User-Agent: MitE1x Chascomus\r\n";
			string expiresf = "Expires: 300\r\n";
			string allowf = "Allow: INVITE, ACK, CANCEL, BYE, REGISTER, SUBSCRIBE, NOTIFY, REFER, OPTIONS, INFO\r\n";
			string early_supf = "P-Early-Media: Supported\r\n";
			string identityf = "P-Asserted-Identity: \"Eugenio Voss\" <sip:5409@192.168.41.245>\r\n";
			string idllamadaf = "P-Mitrol-idLlamada: 180314120413252_MIT_11118\r\n";
			string ruteof = "P-Mitrol-PerfilRuteo: 1\r\n";
			string lengthf = "Content-Length: 381\r\n";
			string typef = "Content-Type: application/sdp\r\n\r\n";

			string lineaf = methodf + viaf + fromf + tof + callidf + seqf + contactf
				+ forwardf + agentf + expiresf + allowf + early_supf + identityf
				+ idllamadaf + ruteof + lengthf + typef;

			string verf = "v=0\r\n";
			string ownerf = "o=5409 0 0 IN IP4 192.168.41.245\r\n";
			string sessionf = "s = MitE1x Call\r\n";
			string connf = "c=IN IP4 192.168.41.230\r\n";
			string tf = "t=0 0\r\n";
			string mediaf = "m=audio 35102 RTP/AVP 0 8 4 18 9 97 2 101\r\n";

			//lineaf = lineaf + verf + ownerf + sessionf + connf + tf +
			//	mediaf + attr + pcmu + pcma + g723 + g729 + annexb + g722 +
			//	ilbc + rtpmap + tel_event + fmtp;

			unique_ptr<Invite> s = unique_ptr<Invite>((Invite *)Sip::buildMessage(linea));//(sip::Sip *)new sip::Sip(linea, "");
			unique_ptr<Invite> d = unique_ptr<Invite>((Invite *)s->clone());//(sip::Sip *)new sip::Sip(linea, "");
			Uri * ui = d->getSipUri();
			*ui = "sip:8036@192.168.41.227";
			From * f = (From *)d->getFrom();
			*f = d->getTo()->to_string();
			SipUri *fui = (SipUri *)f->getSipUri();
			fui->setUser("5409");
			f->add("tag=572389300");
			To *t = (To *)d->getTo();
			*t = tof;
			Uri *u = d->getVia()->getUri();
			*u = "192.168.41.245:10002;rport;branch=z9hG4bKddsEurK18523f00.sa23048ptb7Rm";
			SipHeader* h= (SipHeader *)d->getHeader(constHeader::callidHeader);
			*h = "Call-ID: 205684380-0@192.168.41.245";
			To *ctct = (To *)d->getHeader(constHeader::contactHeader);
			*ctct = contactf;
			h = (SipHeader *)d->getHeader(constHeader::forwardsHeader);
			*h = "Max-Forwards: 69";
			h = (SipHeader *)d->getHeader(constHeader::uaHeader);
			*h = "User-Agent: MitE1x Chascomus";
			f = (From *)d->getHeader(constHeader::identHeader);
			*f = identityf;

										   //voy comparando linea a linea
			string result = d->to_string();// << endl;
			test(lineaf, result);
		}
	};
};