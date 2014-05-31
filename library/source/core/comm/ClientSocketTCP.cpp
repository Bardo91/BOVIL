/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-05-31
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ClientSocketTCP.h"

#include <cassert>

namespace BOViL{
	namespace comm{
		ClientSocketTCP::ClientSocketTCP(const std::string &_serverIp, const std::string &_serverPort): mServerIp(_serverIp), mServerPort(_serverPort){
			memset(&mHints, 0, sizeof(mHints));
			
			mHints.ai_family = AF_INET;			// Connect to ip v4 or v6
			mHints.ai_socktype = SOCK_STREAM;	// Connection tipe TCP IP
			mHints.ai_protocol = IPPROTO_TCP;

			// Geting address info
			int iResult = getaddrinfo(mServerIp.c_str(), mServerPort.c_str(), &mHints, &mResults);
			if (iResult != 0) {
				closeSocket();

				assert(false);
			}

			// Initializing socket
			// Attempt to connect to an address until one succeeds
			for (mPtr = mResults; mPtr != NULL; mPtr = mPtr->ai_next) {
				// Create a SOCKET for connecting to server
				mSocket = socket(mPtr->ai_family, mPtr->ai_socktype, mPtr->ai_protocol);
				if (mSocket == INVALID_SOCKET) {
					closeSocket();
					assert(false);
				}

				// Connect to server.
				int iResult = connect(mSocket, mPtr->ai_addr, (int)mPtr->ai_addrlen);
				if (iResult == SOCKET_ERROR) {
					closeSocket();
					mSocket = INVALID_SOCKET; 
					continue;
				}
				break;
			}

			freeaddrinfo(mResults);

			if (mSocket == INVALID_SOCKET) {
				closeSocket();
				assert(false);
			}
		}
	}	//	namespace comm
}	//	namespace BOViL
