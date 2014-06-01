/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-06-01
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ServerSocketUDP.h"

#include <cassert>

namespace BOViL{
	namespace comm{
		//-------------------------------------------------------------------------------
		ServerSocketUDP::ServerSocketUDP(const std::string &_serverPort) : mServerPort(_serverPort) {
			memset(&mHints, 0, sizeof(mHints));
			mHints.ai_family = AF_INET;
			mHints.ai_socktype = SOCK_DGRAM;
			mHints.ai_protocol = IPPROTO_UDP;
			mHints.ai_flags = AI_PASSIVE;

			// Resolve the server address and port
			if (getaddrinfo(NULL, mServerPort.c_str(), &mHints, &mResult) != 0) {
				closeSocket();
				assert(false);
			}

			// Create a SOCKET for connecting to server
			mSocket = socket(mResult->ai_family, mResult->ai_socktype, mResult->ai_protocol);
			if (mSocket == INVALID_SOCKET) {
				closeSocket();
				freeaddrinfo(mResult);
				assert(false);
			}

			if (bind(mSocket, mResult->ai_addr, mResult->ai_addrlen) == SOCKET_ERROR) {
				freeaddrinfo(mResult);
				closeSocket();
				assert(false);
			}

			freeaddrinfo(mResult);
		}
	}	//	namespace comm
}	//	namespace BOViL