#include "stdafx.h"
#include "CppUnitTest.h"
#include "../sipsdk/sipRequest.h"
#include "../sipsdk/SipException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sip;
using namespace std;

namespace SipTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
	public:
		TEST_METHOD(TestInvite)
		{
			// TODO: Agregar aquí el código de la prueba
			string invite = "INVITE sip:8036@192.168.41.245 SIP/2.0\r\n";
			string via = "Via: SIP / 2.0 / UDP 192.168.41.230 : 11121; rport; branch = z9hG4bKddsEurK4164f00.sa12088ptb7Rm\r\n";
			string from = "From: \"Eugenio Voss\" <sip : 5409@192.168.41.230>; tag = 296737002\r\n";
			string to = "To: <sip : 8036@192.168.41.245>\r\n";
			string callid = "Call-ID: 82814277 - 1@192.168.41.230\r\n";
			string seq = "CSeq: 1 INVITE\r\n";
			string contact = "Contact: <sip : 5409@192.168.41.230:11121; transport = udp>\r\n";
			string max = "Max-Forwards: 70\r\n";
			string uag = "User-Agent: MitE1xv4.4.5.973\r\n";
			string expires = "Expires: 300\r\n";
			string allow = "Allow: INVITE, ACK, CANCEL, BYE, REGISTER, SUBSCRIBE, NOTIFY, REFER, OPTIONS, INFO\r\n";
			string early = "P-Early-Media: Supported\r\n";
			string ident = "P-Asserted-Identity: \"Eugenio Voss\" <sip : 5409@192.168.41.230>\r\n";
			string llamada = "P-Mitrol-idLlamada: 180314120413252_MIT_11118\r\n";
			string ruteo = "P-Mitrol-PerfilRuteo: 1\r\n";
			string length = "Content-Length: 381\r\n";
			string type = "Content-Type: application / sdp\r\n\r\n";

			//string sdp = "v=0\r\no = 5409 0 0 IN IP4 192.168.41.230\r\ns = MitE1x Call\r\nc = IN IP4 192.168.41.230\r\nt = 0 0\r\n";
			//string media = "m=audio 35102 RTP / AVP 0 8 4 18 9 97 2 101\r\na = sendrecv\r\n";
			//string codecs = "a=rtpmap:0 PCMU / 8000 / 1\r\na = rtpmap : 8 PCMA / 8000 / 1\r\na = rtpmap : 4 G723 / 8000 / 1\r\na = rtpmap : 18 G729 / 8000 / 1\r\n";
			//string codecs2 = "a=fmtp : 18 annexb = no\r\na = rtpmap : 9 G722 / 8000 / 1\r\na = rtpmap : 97 iLBC / 8000 / 1\r\na = rtpmap : 2 2 / 8000 / 1\r\n";
			//string dtmf = "a=rtpmap : 101 telephone - event / 8000\r\na = fmtp : 101 0 - 15\r\n";

			string linea = invite + via + from + to + callid + seq + contact + max + uag + expires + allow + early + ident +
				llamada + ruteo + length + type;
			//linea += sdp + media + codecs + codecs2 + dtmf;

			sip::Sip *s = (sip::Sip *)new sip::Sip(linea);
			string result = s->to_string();// << endl;
			
			//voy comparando linea a linea
			size_t ar = 0;
			size_t al = 0;
			size_t pr = result.find_first_of(da);
			size_t pl = linea.find_first_of(da);
			while (pr >= 0 && pl >= 0)
			{
				string sr = result.substr(ar, pr-ar);
				string sl = linea.substr(al, pl-ar);
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
			delete s;
		}

		TEST_METHOD(Test200OK)
		{
			string request = "SIP / 2.0 200 OK\r\n";
			string via = "Via: SIP/2.0/UDP 192.168.41.245:10002;rport;branch=z9hG4bKddsEurK18523f00.sa23048ptb7Rm\r\n";
			string from = "From: \"Eugenio Voss\" <sip : 5409@192.168.41.245>; tag = 572389300\r\n";
			string to = "To: <sip : 8036@192.168.41.227>; tag = 167348820\r\n";
			string callid = "Call - ID: 205684380 - 0@192.168.41.245\r\n";
			string seq = "CSeq: 1 INVITE\r\n";
			string contact = "Contact : <sip : 8036@192.168.41.227:5060; transport = udp>\r\n";
			string server = "Server : MitE1x Chascomus\r\n";
			//string P-Mitrol-idLlamada : 180314120413252_MIT_11118
			string allow = "Allow : INVITE, ACK, CANCEL, BYE, REGISTER, SUBSCRIBE, NOTIFY, REFER, OPTIONS, INFO\r\n";
			string length = "Content-Length : 203\r\n";
			string type = "Content-Type : application / sdp\r\n\r\n";

			//string sdp = "v = 0\r\no = 5409 0 0 IN IP4 192.168.41.227\r\ns = MitE1x Call\r\nc = IN IP4 192.168.41.227\r\nt = 0 0\r\n";
			//string media = "m = audio 35122 RTP / AVP 0 101\r\na = sendrecv\r\n";
			//string codecs = "a = rtpmap:0 PCMU / 8000 / 1\r\na = rtpmap : 101 telephone - event / 8000\r\na = fmtp : 101 0 - 15\r\n";

			string linea = request + via + from + to + callid + seq + contact + allow + length + type;
			//linea += sdp + media + codecs;

			sip::Sip *s = (sip::Sip *)new sip::Sip(linea);
			string result = s->to_string();// << endl;
			int c = linea.compare(result);
			if (c != 0)
				throw exception();
			//Assert::AreEqual(result, linea);
			delete s;
		}
		TEST_METHOD(TestAck)
		{
			// TODO: Agregar aquí el código de la prueba
			string ack = "ACK sip:8036@192.168.41.227:5060 SIP/2.0\r\n";
			string via = "Via: SIP / 2.0 / UDP 192.168.41.245 : 10002; rport; branch = z9hG4bKddsEurK26571f00.sa30252ptb7Rm\r\n";
			string from = "From : \"Eugenio Voss\" <sip : 5409@192.168.41.245>; tag = 572389300\r\n";
			string to = "To: <sip : 8036@192.168.41.227>; tag = 167348820\r\n";
			string callid = "Call - ID: 205684380 - 0@192.168.41.245\r\n";
			string seq = "CSeq: 1 ACK\r\n";
			string max = "Max - Forwards : 70\r\n";
			string uagent = "User - Agent : MitE1x Chascomus\r\n";
			string content = "Content - Length : 0\r\n\r\n";
			string linea = ack + via + from + to + callid + seq + max + uagent + content;

			sip::Sip *s = (sip::Sip *)new sip::Sip(linea);
			//sip::SipRequest *req = s->buildRequest();
			string result = s->to_string();// << endl;
			Assert::AreEqual(result, linea);
			delete s;
		}

	};
}