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
			// Socket configuration
			memset(&mHints, 0, sizeof(mHints));
			mHints.ai_family = AF_INET;
			mHints.ai_socktype = SOCK_DGRAM;
			mHints.ai_protocol = IPPROTO_UDP;
			mHints.ai_flags = AI_PASSIVE;

			// Initialize socket
			mSocket = socket(mHints.ai_family, mHints.ai_socktype, mHints.ai_protocol);
			if (mSocket == INVALID_SOCKET){
				closeSocket();
				assert(false);
			}
			
			// Set up a SOCKADDR_IN structure that will tell bind that we
			// want to receive datagrams from all interfaces using port _serverPort.
			mAddr.sin_family = AF_INET;
			mAddr.sin_port = htons((USHORT) atoi(_serverPort.c_str()));
			mAddr.sin_addr.s_addr = htonl(INADDR_ANY);

			if (bind(mSocket, (sockaddr*)&mAddr, sizeof(mAddr)) == SOCKET_ERROR){
				closeSocket();
				assert(false);

			}


			// 666 TODO: ver como meter el request de información del otro lado del socket etc...

			//-------------------------------------------------------------------------------------
			//memset(&mHints, 0, sizeof(mHints));
			//mHints.ai_family = AF_INET;
			//mHints.ai_socktype = SOCK_DGRAM;
			//mHints.ai_protocol = IPPROTO_UDP;
			//mHints.ai_flags = AI_PASSIVE;
			//
			//// Resolve the server address and port
			//if (getaddrinfo(NULL, mServerPort.c_str(), &mHints, &mResult) != 0) {
			//	closeSocket();
			//	assert(false);
			//}
			//
			//// Create a SOCKET for connecting to server
			//mSocket = socket(mResult->ai_family, mResult->ai_socktype, mResult->ai_protocol);
			//if (mSocket == INVALID_SOCKET) {
			//	closeSocket();
			//	freeaddrinfo(mResult);
			//	assert(false);
			//}
			//
			//if (bind(mSocket, mResult->ai_addr, mResult->ai_addrlen) == SOCKET_ERROR) {
			//	freeaddrinfo(mResult);
			//	closeSocket();
			//	assert(false);
			//}
			//
			//freeaddrinfo(mResult);
		}
	}	//	namespace comm
}	//	namespace BOViL