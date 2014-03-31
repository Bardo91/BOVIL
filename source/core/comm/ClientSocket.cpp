/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-29
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ClientSocket.h"

#include <cassert>
#include <sstream>

namespace BOViL{
	namespace comm{
		//-----------------------------------------------------------------------------
		ClientSocket::ClientSocket(const std::string _ip, const std::string _port){
			mServerIp = _ip;
			mServerPort = _port;
			mSocket = INVALID_SOCKET;
			mResult = nullptr;
			mPtr = nullptr;

			// Initialize Winsock
			int iResult = WSAStartup(MAKEWORD(2,2), &mWsaData);
			if (iResult != 0) {
				printf("WSAStartup failed with error: %d\n", iResult);
				assert(false);
			}

			memset( &mHints, 0, sizeof(mHints));
			mHints.ai_family = AF_UNSPEC;
			mHints.ai_socktype = SOCK_STREAM;
			mHints.ai_protocol = IPPROTO_TCP;

		}
		//-----------------------------------------------------------------------------
		int ClientSocket::initializeSocket(){
			// Resolve the server address and port
			int iResult = getaddrinfo(mServerIp.c_str(), mServerPort.c_str(), &mHints, &mResult);
			if ( iResult != 0 ) {
				printf("getaddrinfo failed with error: %d\n", iResult);
				WSACleanup();
				return 1;
			}

			// Attempt to connect to an address until one succeeds
			for(mPtr=mResult; mPtr != NULL ;mPtr=mPtr->ai_next) {

				// Create a SOCKET for connecting to server
				mSocket = socket(mPtr->ai_family, mPtr->ai_socktype, mPtr->ai_protocol);
				if (mSocket == INVALID_SOCKET) {
					printf("socket failed with error: %ld\n", WSAGetLastError());
					WSACleanup();
					return 1;
				}

				// Connect to server.
				iResult = connect( mSocket, mPtr->ai_addr, (int) mPtr->ai_addrlen);
				if (iResult == SOCKET_ERROR) {
					closesocket(mSocket);
					mSocket = INVALID_SOCKET;
					continue;
				}
				break;
			}

			freeaddrinfo(mResult);

			if (mSocket == INVALID_SOCKET) {
				printf("Unable to connect to server!\n");
				WSACleanup();
				return 1;
			}

			return 0;
		}
		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
		int ClientSocket::sendData(std::string _data){
			int iResult = send( mSocket, _data.c_str(), (int)_data.size(), 0 );
			if (iResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(mSocket);
				WSACleanup();
				return 1;
			}

			return 0;
		}
		//-----------------------------------------------------------------------------
		
	}	//	namespace comm
}	//	namespace BOViL