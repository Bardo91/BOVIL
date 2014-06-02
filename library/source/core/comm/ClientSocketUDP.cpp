/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-05-31
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ClientSocketUDP.h"

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
			mAddr.sin_family = AF_INET;
			mAddr.sin_port = htons((USHORT)atoi(_serverPort.c_str()));
			mAddr.sin_addr.s_addr = inet_addr(_serverIp.c_str());

			// 666 TODO: ver como meter el request de información del otro lado del socket etc...

			//-------------------------------------------------------------------------------------
			//memset(&mHints, 0, sizeof(mHints));
			//mHints.ai_family = AF_INET;			// Connect to ip v4 or v6
			//mHints.ai_socktype = SOCK_DGRAM;	// Connection tipe UDP IP
			//mHints.ai_protocol = IPPROTO_UDP;
			//
			//// Geting address info
			//int iResult = getaddrinfo(mServerIp.c_str(), mServerPort.c_str(), &mHints, &mResults);
			//if (iResult != 0) {
			//	closeSocket();
			//
			//	assert(false);
			//}
			//
			//// Initializing socket
			//// Attempt to connect to an address until one succeeds
			//for (mPtr = mResults; mPtr != NULL; mPtr = mPtr->ai_next) {
			//	// Create a SOCKET for connecting to server
			//	mSocket = socket(mPtr->ai_family, mPtr->ai_socktype, mPtr->ai_protocol);
			//	if (mSocket == INVALID_SOCKET) {
			//		closeSocket();
			//		assert(false);
			//	}
			//
			//	if (bind(mSocket, mPtr->ai_addr, mPtr->ai_addrlen) == SOCKET_ERROR) {
			//		freeaddrinfo(mPtr);
			//		closeSocket();
			//		continue;
			//	}
			//
			//	break;
			//}
			//
			//freeaddrinfo(mResults);
			//
			//if (mSocket == INVALID_SOCKET) {
			//	closeSocket();
			//	assert(false);
			//}
		}
	}	//	namespace comm
}	//	namespace BOViL
