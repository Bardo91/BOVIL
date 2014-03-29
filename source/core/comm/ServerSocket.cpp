/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-27
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ServerSocket.h"

#include <cassert>
#include <sstream>

namespace BOViL{
	namespace comm{
		//-----------------------------------------------------------------------------
		ServerSocket::ServerSocket(){
			// Initialize Winsock
			int iResult = WSAStartup(MAKEWORD(2,2), &mWsaData);
			if (iResult != 0) {
				printf("WSAStartup failed with error: %d\n", iResult);
				assert(false);
			}

			memset(&mHints, 0, sizeof(mHints));
			mHints.ai_family = AF_INET;
			mHints.ai_socktype = SOCK_STREAM;
			mHints.ai_protocol = IPPROTO_TCP;
			mHints.ai_flags = AI_PASSIVE;
		}

		//-----------------------------------------------------------------------------
		int ServerSocket::initializeSocket(std::string& _port){
			// Resolve the server address and port
			int iResult = getaddrinfo(NULL, _port.c_str(), &mHints, &mResult);
			if ( iResult != 0 ) {
				printf("getaddrinfo failed with error: %d\n", iResult);
				WSACleanup();
				return 1;
			}

			// Create a SOCKET for connecting to server
			mServerSocket = socket(mResult->ai_family, mResult->ai_socktype, mResult->ai_protocol);
			if (mServerSocket == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				freeaddrinfo(mResult);
				WSACleanup();
				return 1;
			}

			// Setup the TCP listening socket
			iResult = bind( mServerSocket, mResult->ai_addr, (int)mResult->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				printf("bind failed with error: %d\n", WSAGetLastError());
				freeaddrinfo(mResult);
				closesocket(mServerSocket);
				WSACleanup();
				return 1;
			}

			freeaddrinfo(mResult);

			iResult = listen(mServerSocket, SOMAXCONN);
			if (iResult == SOCKET_ERROR) {
				printf("listen failed with error: %d\n", WSAGetLastError());
				closesocket(mServerSocket);
				WSACleanup();
				return 1;
			}
			return 0;
		}
		//-----------------------------------------------------------------------------
		int ServerSocket::acceptClient(){
			// Accept a client socket
			mClientSocket = accept(mServerSocket, NULL, NULL);
			if (mClientSocket == INVALID_SOCKET) {
				printf("accept failed with error: %d\n", WSAGetLastError());
				closesocket(mServerSocket);
				WSACleanup();
				
				return 1;
			}

			// No longer need server socket
			closesocket(mServerSocket);
			
			return 0;
		}
		//-----------------------------------------------------------------------------
		std::string ServerSocket::receiveStr() {
			char recvbuf[1024];
			int recvbuflen = 1024;

			int iResult = recv(mClientSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0) {
				printf("Bytes received: %d\n", iResult);
				return "ERROR";
			}

			return std::string(recvbuf);
		}

		//-----------------------------------------------------------------------------
		int ServerSocket::sendStr(std::string& _str) {
			// Echo the buffer back to the sender
			int iResult;
			int iSendResult = send( mClientSocket, _str.c_str(), iResult, 0 );
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(mClientSocket);
				WSACleanup();
				return 1;
			}
			printf("Bytes sent: %d\n", iSendResult);
			
		}
		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
		
		//-----------------------------------------------------------------------------
		
	}	//	namespace comm
}	//	namespace BOViL