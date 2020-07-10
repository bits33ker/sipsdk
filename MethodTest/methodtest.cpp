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
#include "../sipsdk/SessionDescription.h"
#include "../sipsdk/SipException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sip;
using namespace std;

namespace methodtest
{		
	TEST_CLASS(MethodTest)
	{
		void test(string linea, string result)throw(SipException)
		{
			size_t ar = 0;
			size_t al = 0;
			size_t pr = result.find_first_of(da);
			size_t pl = linea.find_first_of(da);
			while (pr >= 0 && pl >= 0 && pl<linea.length())
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
		
		TEST_METHOD(TestTo)
		{
			string to = "<sip:8036@192.168.41.245>";
			HeaderContact * sip = (HeaderContact *)new To(constHeader::toHeader, to);
			Assert::AreEqual(sip->to_string(), "To: " + to);
		}

		TEST_METHOD(TestFrom)
		{
			string from = "\"Eugenio Voss\" <sip:5409@192.168.41.230>;tag=296737002";
			From * f = (From *)new From("From",from);
			*f = from;
			Assert::AreEqual(from, f->to_string());
		}

		TEST_METHOD(TestContact)
		{
			string contact = "<sip:5409@192.168.41.230:11121;transport=udp>";
			HeaderContact * sip = (HeaderContact *)new To(constHeader::contactHeader, contact);
			Assert::AreEqual(sip->to_string(),"Contact: " + contact);
		}

		TEST_METHOD(TestVia)
		{
			string via = "Via: SIP/2.0/UDP 192.168.41.230:11121;rport;branch=z9hG4bKddsEurK4164f00.sa12088ptb7Rm";
			Via * sip = (Via *)new Via(via);
			Assert::AreEqual(sip->to_string(), via);
		}
		TEST_METHOD(TestInvite)
		{
			// TODO: Agregar aquí el código de la prueba
			string invite = "INVITE sip:8036@192.168.41.245 SIP/2.0\r\n";
			string via = "Via: SIP/2.0/UDP 192.168.41.230:11121;rport;branch=z9hG4bKddsEurK4164f00.sa12088ptb7Rm\r\n";
			string from = "From: \"Eugenio Voss\" <sip:5409@192.168.41.230>;tag=296737002\r\n";
			string to = "To: <sip:8036@192.168.41.245>\r\n";
			string callid = "Call-ID: 82814277-1@192.168.41.230\r\n";
			string seq = "CSeq: 1 INVITE\r\n";
			string contact = "Contact: <sip:5409@192.168.41.230:11121;transport=udp>\r\n";
			string max = "Max-Forwards: 70\r\n";
			string uag = "User-Agent: MitE1xv4.4.5.973\r\n";
			string expires = "Expires: 300\r\n";
			string allow = "Allow: INVITE,ACK,CANCEL,BYE,REGISTER,SUBSCRIBE,NOTIFY,REFER,OPTIONS,INFO\r\n";
			string early = "P-Early-Media: Supported\r\n";
			string ident = "P-Asserted-Identity: \"Eugenio Voss\" <sip:5409@192.168.41.230>\r\n";
			string llamada = "P-Mitrol-idLlamada: 180314120413252_MIT_11118\r\n";
			string ruteo = "P-Mitrol-PerfilRuteo: 1\r\n";
			string length = "Content-Length: 381\r\n";
			string type = "Content-Type: application/sdp\r\n\r\n";

			string sdp = "v=0\r\no=5409 0 0 IN IP4 192.168.41.230\r\ns=MitE1x Call\r\nc=IN IP4 192.168.41.230\r\nt=0 0\r\n";
			string media = "m=audio 35102 RTP/AVP 0 8 4 18 9 97 2 101\r\na=sendrecv\r\n";
			string codecs = "a=rtpmap:0 PCMU/8000/1\r\na=rtpmap:8 PCMA/8000/1\r\na=rtpmap:4 G723/8000/1\r\na=rtpmap:18 G729/8000/1\r\n";
			string codecs2 = "a=fmtp:18 annexb=no\r\na=rtpmap:9 G722/8000/1\r\na=rtpmap:97 iLBC/8000/1\r\na=rtpmap:2 2/8000/1\r\n";
			string dtmf = "a=rtpmap:101 telephone-event/8000\r\na=fmtp:101 0-15\r\n";

			string linea = invite + via + from + to + callid + seq + contact + max + uag + expires + allow + early + ident +
				llamada + ruteo + length + type;
			linea += sdp + media + codecs + codecs2 + dtmf;

			unique_ptr<Invite> s = unique_ptr<Invite>((Invite *)Sip::buildMessage(linea));//(sip::Sip *)new sip::Sip(linea, "");
			string result = s->to_string();// << endl;

		   //voy comparando linea a linea
			test(linea, result);
		}

		TEST_METHOD(TestInviteOK)
		{
			// TODO: Agregar aquí el código de la prueba
			string invite = "SIP/2.0 200 OK\r\n";
			string via = "Via: SIP/2.0/UDP 192.168.41.230:11121;rport;branch=z9hG4bKddsEurK4164f00.sa12088ptb7Rm\r\n";
			string from = "From: \"Eugenio Voss\" <sip:5409@192.168.41.230>;tag=296737002\r\n";
			string to = "To: <sip:8036@192.168.41.227>;tag=167348820\r\n";
			string callid = "Call-ID: 82814277-1@192.168.41.230\r\n";
			string seq = "CSeq: 1 INVITE\r\n";
			string contact = "Contact: <sip:5409@192.168.41.230:11121;transport=udp>\r\n";
			string max = "Max-Forwards: 70\r\n";
			string server = "Server: MitE1x Chascomus\r\n";
			string expires = "Expires: 300\r\n";
			string allow = "Allow: INVITE,ACK,CANCEL,BYE,REGISTER,SUBSCRIBE,NOTIFY,REFER,OPTIONS,INFO\r\n";
			string early = "P-Early-Media: Supported\r\n";
			string ident = "P-Asserted-Identity: \"Eugenio Voss\" <sip:5409@192.168.41.230>\r\n";
			string llamada = "P-Mitrol-idLlamada: 180314120413252_MIT_11118\r\n";
			string ruteo = "P-Mitrol-PerfilRuteo: 1\r\n";
			string length = "Content-Length: 381\r\n";
			string owner = "o=5409 0 0 IN IP4 192.168.41.227\r\n";
			string type = "Content-Type: application/sdp\r\n\r\n";

			//string sdp = "v=0\r\no = 5409 0 0 IN IP4 192.168.41.230\r\ns = MitE1x Call\r\nc = IN IP4 192.168.41.230\r\nt = 0 0\r\n";
			//string media = "m=audio 35102 RTP / AVP 0 8 4 18 9 97 2 101\r\na = sendrecv\r\n";
			//string codecs = "a=rtpmap:0 PCMU / 8000 / 1\r\na = rtpmap : 8 PCMA / 8000 / 1\r\na = rtpmap : 4 G723 / 8000 / 1\r\na = rtpmap : 18 G729 / 8000 / 1\r\n";
			//string codecs2 = "a=fmtp : 18 annexb = no\r\na = rtpmap : 9 G722 / 8000 / 1\r\na = rtpmap : 97 iLBC / 8000 / 1\r\na = rtpmap : 2 2 / 8000 / 1\r\n";
			//string dtmf = "a=rtpmap : 101 telephone - event / 8000\r\na = fmtp : 101 0 - 15\r\n";

			string linea = invite + via + from + to + callid + seq + contact + max + server + expires + allow + early + ident +
				llamada + ruteo + length + type;
			//linea += sdp + media + codecs + codecs2 + dtmf;

			unique_ptr<SipResponse> s = unique_ptr<SipResponse>((SipResponse *)Sip::buildMessage(linea));
			string result = s->to_string();// << endl;

		   //voy comparando linea a linea
			test(linea, result);
		}

		TEST_METHOD(TestSdp)
		{
			string version = "v=0\r\n";
			string owner = "o=5409 0 0 IN IP4 192.168.41.230\r\n";
			string session = "s=MitE1x Call\r\n";
			string connection = "c=IN IP4 192.168.41.227\r\n";
			string tiempo = "t=0 0\r\n";
			string media_desc = "m=audio 35122 RTP/AVP 0 101\r\n";
			string media_attr = "a=sendrecv\r\n";
			string codec = "a=rtpmap:0 PCMU/8000/1\r\n";
			string rtpmap = "a=rtpmap:101 telephone-event/8000\r\n";
			string fmtp = "a=fmtp:101 0-15\r\n";

			string linea = version + owner + session + connection + tiempo
				+ media_desc + media_attr + codec + rtpmap + fmtp;

			sip::SessionDescription *s = (sip::SessionDescription *)new sip::SessionDescription(linea);
			string result = s->to_string();// << endl;

		   //voy comparando linea a linea
			test(linea, result);
			delete s;
		}
		TEST_METHOD(TestTry)
		{
			string method = "SIP/2.0 100 Trying\r\n";
			string via = "Via: SIP/2.0/UDP 192.168.41.230:11121;rport;branch=z9hG4bKddsEurK4164f00.sa12088ptb7Rm\r\n";
			string from = "From: \"Eugenio Voss\" <sip:5409@192.168.41.230>;tag=296737002\r\n";
			string to = "To: <sip:8036@192.168.41.245>;tag=858665926\r\n";
			string callid = "Call-ID: 82814277-1@192.168.41.230\r\n";
			string seq = "CSeq: 1 INVITE\r\n";
			string server = "Server: MitE1x Chascomus\r\n";
			string idllamada = "P-Mitrol-idLlamada: 180314120413252_MIT_11118\r\n";
			string length = "Content-Length: 0\r\n\r\n";

			string linea = method + via + from + to + callid + seq + server + length;

			unique_ptr<SipResponse> s = unique_ptr<SipResponse>((SipResponse *)Sip::buildMessage(linea));
			string result = s->to_string();// << endl;

										   //voy comparando linea a linea
			test(linea, result);
		}
		TEST_METHOD(TestRing)
		{
			string method = "SIP/2.0 180 Ringing\r\n";
			string via = "Via: SIP/2.0/UDP 192.168.41.245:10002;rport;branch=z9hG4bKddsEurK18523f00.sa23048ptb7Rm\r\n";
			string from = "From: \"Eugenio Voss\" <sip:5409@192.168.41.245>;tag=572389300\r\n";
			string to = "To: <sip:8036@192.168.41.227>;tag=167348820\r\n";
			string callid = "Call-ID: 205684380-0@192.168.41.245\r\n";
			string seq = "CSeq: 1 INVITE\r\n";
			string server = "Server: MitE1x Chascomus\r\n";
			string allow = "Allow: INVITE,ACK,CANCEL,BYE,REGISTER,SUBSCRIBE,NOTIFY,REFER,OPTIONS,INFO\r\n";
			string llamada = "P-Mitrol-idLlamada: 180314120413252_MIT_11118\r\n";
			string length = "Content-Length: 0\r\n\r\n";

			string linea = method + via + from + to + callid + seq + server + allow + llamada + length;

			unique_ptr<SipResponse> s = unique_ptr<SipResponse>((SipResponse *)Sip::buildMessage(linea));
			string result = s->to_string();// << endl;

										   //voy comparando linea a linea
			test(linea, result);
		}
		TEST_METHOD(TestSessionProgress)
		{
			string method = "SIP/2.0 183 Session Progress\r\n";
			string via = "Via: SIP/2.0/UDP 192.168.41.245:10006;rport;branch=z9hG4bKddsEurK22566f00.sa3270ptb7Rm\r\n";
			string from = "From: \"User2\" <sip:5409@192.168.41.245>;tag=59913372\r\n";
			string to = "To: <sip:8036@192.168.40.130>;tag=167613747\r\n";
			string callid = "Call-ID: 289634157-0@192.168.41.245\r\n";
			string seq = "CSeq: 1 INVITE\r\n";
			string server = "Server: MitSoftphone v1.0.0\r\n";
			string allow = "Allow: INVITE,ACK,CANCEL,BYE,REGISTER,SUBSCRIBE,NOTIFY,REFER,OPTIONS,INFO\r\n";
			string length = "Content-Length: 203\r\n";
			string type = "Content-Type: application/sdp\r\n\r\n";

			string version = "v=0\r\n";
			string owner = "o=5409 0 0 IN IP4 192.168.40.130\r\n";
			string session = "s=MitE1x Call\r\n";
			string connection = "c=IN IP4 192.168.40.130\r\n";
			string time = "t=0 0\r\n";
			string media = "m=audio 35002 RTP/AVP 0 101\r\n";
			string attr = "a=sendrecv\r\n";
			string codecs = "a=rtpmap:0 PCMU/8000/1\r\na=rtpmap:101 telephone-event/8000\r\n";
			string format = "a=fmtp: 101 0-15\r\n";

			string linea = method + via + from + to + callid + seq + server + allow + length + type;
			//linea += version + owner + session + connection + time + media + attr + codecs + format;

			unique_ptr<SipResponse> s = unique_ptr<SipResponse>((SipResponse *)Sip::buildMessage(linea));
			string result = s->to_string();// << endl;

			//voy comparando linea a linea
			test(linea, result);
		}
		TEST_METHOD(TestAck)
		{
			string method = "ACK sip:8036@192.168.40.130 SIP/2.0\r\n";
			string via = "Via: SIP/2.0/UDP 192.168.41.245:10006;rport;branch=z9hG4bKddsEurK2795f00.sa2550ptb7Rm\r\n";
			string from = "From: \"User2\" <sip:5409@192.168.41.245>;tag=59913372\r\n";
			string to = "To: <sip:8036@192.168.40.130>;tag=167613747\r\n";
			string callid = "Call-ID: 289634157-0@192.168.41.245\r\n";
			string seq = "CSeq: 1 ACK\r\n";
			string max ="Max-Forwards: 70\r\n";
			string agent = "User-Agent: MitE1x v4.3.4.77\r\n";
			string length = "Content-Length: 0\r\n\r\n";

			string linea = method + via + from + to + callid + seq + max + agent + length;

			unique_ptr<Ack>s = unique_ptr<Ack>((Ack *)Sip::buildMessage(linea));
			string result = s->to_string();// << endl;

			test(linea, result);
		}
		TEST_METHOD(TestBye)
		{
			string method = "BYE sip:8036@192.168.41.245 SIP/2.0\r\n";
			string via = "Via: SIP/2.0/UDP 172.30.41.230:10403;rport;branch=z9hG4bKddsEurK15819f00.sa2232ptb7Rm\r\n";
			string from = "From: <sip:5409@172.30.41.230>;tag=102712708\r\n";
			string to = "To: <sip:8036@192.168.41.245>;tag=410140630\r\n";
			string callid = "Call-ID: 708534834-0@172.30.41.230\r\n";
			string seq = "CSeq: 2 BYE\r\n";
			string max = "Max-Forwards: 70\r\n";
			string agent = "User-Agent: MitE1xv4.4.5.973\r\n";
			string reason = "Reason: Q.850;cause=16\r\n";
			string length = "Content-Length: 0\r\n\r\n";

			string linea = method + via + from + to + callid + seq + max + agent + reason + length;

			unique_ptr<Bye>s = unique_ptr<Bye>((Bye*)Sip::buildMessage(linea));
			string result = s->to_string();// << endl;

			test(linea, result);

		}
		TEST_METHOD(TestOptions)
		{
			string method = "OPTIONS sip:8036@192.168.40.130 SIP/2.0\r\n";
			string via = "Via: SIP/2.0/UDP 192.168.41.245:10006;rport;branch=z9hG4bKddsEurK5076f00.sa18954ptb7Rm\r\n";
			string from = "From: <sip: 5409@192.168.41.245>;tag=59913372\r\n";
			string to = "To: <sip: 8036@192.168.40.130>;tag=167613747\r\n";
			string callid = "Call-ID: 289634157-0@192.168.41.245\r\n";
			string seq = "CSeq: 2 OPTIONS\r\n";
			string max = "Max-Forwards: 70\r\n";
			string llamada = "P-Mitrol-idLlamada: 161007142622332_MIT_10119\r\n";
			string accept = "Accept: application/sdp\r\n";
			string length = "Content-Length: 0\r\n\r\n";

			string linea = method + via + from + to + callid + seq + max + accept + llamada + length;
			unique_ptr<Options>s = unique_ptr<Options>((Options *)Sip::buildMessage(linea));
			string result = s->to_string();// << endl;

			test(linea, result);
		}
		TEST_METHOD(TestRegister)
		{
			string method = "REGISTER sip:10.35.0.12:5060 SIP/2.0\r\n";
			string via = "Via: SIP/2.0/UDP 10.35.0.204:58947;rport;branch=z9hG4bKPjwRTtBtqD8qsEKtna4hX1KxY6SaJ90wHL\r\n";
			string max = "Max-Forwards: 70\r\n";
			string from = "From: <sip:942303112@10.35.0.12>;tag=VBmeNCSPRtkNz6-kVZmKlpwA17mNg6gX\r\n";
			string to = "To: <sip:942303112@10.35.0.12>\r\n";
			string callid = "Call-ID: zgCBGbMy.1oIfG5-4dmc7IId75.3Uknr\r\n";
			string seq = "CSeq: 43004 REGISTER\r\n";
			string auth = "Authorization: Digest username =\"942303112\", nonce=\"1f775ba730b3d5ca741b0ecf92413980\", uri=\"sip:10.35.0.12:5060\", response=\"42bda466e5d8e05dc1486c506c1f8d63\", algorithm=md5, opaque=\"c0615d7984bdf7df2680bd5c70b30bfa\"\r\n";
			string agent = "User-Agent: CSipSimple_klte-23/r2457\r\n";
			string contact = "Contact: <sip:942303112@10.35.0.204:58947;ob>\r\n";
			string expires = "Expires: 900\r\n";
			string allow = "Allow: PRACK, INVITE, ACK, BYE, CANCEL, UPDATE, INFO, SUBSCRIBE, NOTIFY, REFER, MESSAGE, OPTIONS\r\n";
			string length = "Content-Length: 0\r\n\r\n";

			string linea = method + via + from + to + callid + seq + contact
				+ max + agent + auth + expires + allow + length;

			unique_ptr<Register>s = unique_ptr<Register>((Register *)Sip::buildMessage(linea));
			string result = s->to_string();// << endl;

			test(linea, result);
		}
		TEST_METHOD(TestSubscribe)
		{
			string method = "SUBSCRIBE sip:942303112@10.35.0.12 SIP/2.0\r\n";
			string via = "Via: SIP/2.0/UDP 10.35.0.204:58947;rport;branch=z9hG4bKPjlua8U3irILw.B9Vpzd2TZXqVPXl-JZ.n\r\n";
			string max = "Max-Forwards: 70\r\n";
			string from = "From: <sip:942303112@10.35.0.12>;tag=y0c-JU4jv2RMlfR5utku7ZphmHxxIJ6E\r\n";
			string to = "To: <sip:942303112@10.35.0.12>\r\n";
			string contact = "Contact: <sip:942303112@10.35.0.204:58947;ob>\r\n";
			string callid = "Call-ID: d6OzpBRAe-efZTDwahq6FbQujy6WkH76\r\n";
			string seq = "CSeq: 19908 SUBSCRIBE\r\n";
			string ev = "Event: message-summary\r\n";
			string expires = "Expires: 3600\r\n";
			string supported = "Supported: replaces, 100rel, timer, norefersub\r\n";
			string accept = "Accept: application/simple-message-summary\r\n";
			string allow_ev = "Allow-Events: presence, message - summary, refer\r\n";
			string agent = "User-Agent: CSipSimple_klte-23/r2457\r\n";
			string length = "Content-Length: 0\r\n\r\n";

			string linea = method + via + from + to + callid + seq + contact
				+ max + agent + ev + supported + accept + allow_ev + expires + length;

			unique_ptr<Subscribe>s = unique_ptr<Subscribe>((Subscribe *)Sip::buildMessage(linea));
			string result = s->to_string();// << endl;

			test(linea, result);
		}
		//TODO: 401 UNAUTHORIZED
	};
}