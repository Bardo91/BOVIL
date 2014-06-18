/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-05-31
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ClientSocketUDP.h"

#if defined(__linux__)
	#include <arpa/inet.h>
#endif
#include <cassert>

namespace BOViL{
	namespace comm{
		ClientSocketUDP::ClientSocketUDP(const std::string &_serverIp, const std::string &_serverPort) : mServerIp(_serverIp), mServerPort(_serverPort){
			
			memset(&mHints, 0, sizeof(mHints));
			mHints.ai_family = AF_INET;			// Connect to ip v4 or v6
			mHints.ai_socktype = SOCK_DGRAM;	// Connection tipe UDP IP
			mHints.ai_protocol = IPPROTO_UDP;

			// Create a new socket
			mSocket = socket(mHints.ai_family, mHints.ai_socktype, mHints.ai_protocol);

			if (mSocket == INVALID_SOCKET){
				closeSocket();
				assert(false);

			}
			
			// Set up a SOCKADDR_IN structure that will identify who we
			// will send datagrams to. For demonstration purposes, let's
			// assume our receiver's IP address is _serverIp and waiting
			// for datagrams on port _serverPort.
			// 666 TODO: bindear al puerto para no tener que hacer el send!
			mAddr.sin_family = AF_INET;
			mAddr.sin_port = htons((unsigned short)atoi(_serverPort.c_str()));
			#if defined(_WIN32)
				mAddr.sin_addr.s_addr = inet_addr(_serverIp.c_str());
			#elif defined(__linux__)
				inet_aton(_serverIp.c_str() , &mAddr.sin_addr);
			#endif

			if (bind(mSocket, (sockaddr*)&mAddr, sizeof(mAddr)) == SOCKET_ERROR){
				closeSocket();
				assert(false);

			}

			// 666 TODO: ver como meter el request de información del otro lado del socket etc...
		}
	}	//	namespace comm
}	//	namespace BOViL
