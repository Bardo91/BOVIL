/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-05-31
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ServerSocketTCP.h"

#include <cassert>

namespace BOViL{
	namespace comm{
		//-------------------------------------------------------------------------------
		ServerSocketTCP::ServerSocketTCP(const std::string &_serverPort): mServerPort(_serverPort), mAcceptSocket(INVALID_SOCKET) {
			memset(&mHints, 0, sizeof(mHints));
			mHints.ai_family = AF_INET;
			mHints.ai_socktype = SOCK_STREAM;
			mHints.ai_protocol = IPPROTO_TCP;
			mHints.ai_flags = AI_PASSIVE;

			// Resolve the server address and port
			if (getaddrinfo(NULL, mServerPort.c_str(), &mHints, &mResult) != 0) {
				closeSocket();
				assert(false);
			}

			// Create a SOCKET for connecting to server
			mAcceptSocket = socket(mResult->ai_family, mResult->ai_socktype, mResult->ai_protocol);
			if (mAcceptSocket == INVALID_SOCKET) {
				closeSocket();
				freeaddrinfo(mResult);
				assert(false);
			}

			// Setup the TCP listening socket
			#ifdef __linux__
				int yes = 1;
				setsockopt(mAcceptSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
			#endif
			#ifdef _WIN32
				bool bOptVal = TRUE;
				int bOptLen = sizeof(bool);
				setsockopt(mAcceptSocket, SOL_SOCKET, SO_REUSEADDR, (char *)bOptVal, bOptLen);
			#endif

			if (bind(mAcceptSocket, mResult->ai_addr, mResult->ai_addrlen) == SOCKET_ERROR) {
				freeaddrinfo(mResult);
				closeSocket();
				assert(false);
			}

			if (listen(mAcceptSocket, SOMAXCONN) == SOCKET_ERROR) {
				closeSocket();
				assert(false);
			}

			freeaddrinfo(mResult);


			mSocket = accept(mAcceptSocket, NULL, NULL);
			if (mSocket == INVALID_SOCKET) {
				closeSocket();
				assert(false);
			}

		}
	}	//	namespace comm
}	//	namespace BOViL
