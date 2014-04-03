/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-03-29
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ClientSocket.h"

#include <cassert>
#include <iostream>
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

			int iResult;

			#if defined (_WIN32)
				// Initialize Winsock
				iResult = WSAStartup(MAKEWORD(2,2), &mWsaData);
				if (iResult != 0) {
					printf("WSAStartup failed with error: %d\n", iResult);
					assert(false);
				}
			#endif

			memset( &mHints, 0, sizeof(mHints));
			mHints.ai_family = AF_UNSPEC;
			mHints.ai_socktype = SOCK_STREAM;
			mHints.ai_protocol = IPPROTO_TCP;

			iResult += initializeSocket();
			iResult += connectSocket();

			assert(!iResult);	// If errors break!

		}

		//-----------------------------------------------------------------------------
		int ClientSocket::sendData(std::string _data){
			int iResult = send( mSocket, _data.c_str(), _data.size(), 0 );
			if (iResult == SOCKET_ERROR) {
				std::cout << "Socket Error" << std::endl;
				closesocket(mSocket);
				#if defined (_WIN32)
					std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
					WSACleanup();
				#endif
				return 1;
			}

			return 0;

		}
		//-----------------------------------------------------------------------------
		std::string ClientSocket::receiveData(){
			char recvbuf[1024];
			int recvbuflen = 1024;

			int iResult = recv(mSocket, recvbuf, recvbuflen, 0);
			if (iResult < 0) {
				return "ERROR";
			}

			printf("Bytes received: %d\n", iResult);
			return std::string(recvbuf);

		}

		//-----------------------------------------------------------------------------
		int ClientSocket::initializeSocket(){
			// Resolve the server address and port
			int iResult = getaddrinfo(mServerIp.c_str(), mServerPort.c_str(), &mHints, &mResult);
			if ( iResult != 0 ) {
				std::cout << "etaddrinfo failed with error: " << iResult << std::endl;
				#if defined (_WIN32)
					WSACleanup();
				#endif
				return 1;
			}

			return 0;
		}
		//-----------------------------------------------------------------------------
		int ClientSocket::connectSocket(){
			// Attempt to connect to an address until one succeeds
			for(mPtr=mResult; mPtr != NULL ;mPtr=mPtr->ai_next) {

				// Create a SOCKET for connecting to server
				mSocket = socket(mPtr->ai_family, mPtr->ai_socktype, mPtr->ai_protocol);
				if (mSocket == INVALID_SOCKET) {
					std::cout << "Socket Error" << std::endl;
					#if defined (_WIN32)
						std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
						WSACleanup();
					#endif
					return 1;
				}

				// Connect to server.
				int iResult = connect( mSocket, mPtr->ai_addr, (int) mPtr->ai_addrlen);
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
				#if defined (_WIN32)
					WSACleanup();
				#endif
				return 1;
			}

			return 0;
		}

		//-----------------------------------------------------------------------------
		
	}	//	namespace comm
}	//	namespace BOViL
