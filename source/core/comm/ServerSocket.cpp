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
		ServerSocket::ServerSocket(const std::string _port){
			mPort = _port;
			mSocket = INVALID_SOCKET;
			mClientSocket = INVALID_SOCKET;
			mResult = nullptr;
			#if defined (_WIN32)
				// Initialize Winsock
				int iResult = WSAStartup(MAKEWORD(2,2), &mWsaData);
				if (iResult != 0) {
					printf("WSAStartup failed with error: %d\n", iResult);
					assert(false);
				}
			#endif

			memset(&mHints, 0, sizeof(mHints));
			mHints.ai_family = AF_INET;
			mHints.ai_socktype = SOCK_STREAM;
			mHints.ai_protocol = IPPROTO_TCP;
			mHints.ai_flags = AI_PASSIVE;

			iResult += initializeSocket();
			iResult += connectSocket();

			assert(!iResult);	// If errors break!

		}

		//-----------------------------------------------------------------------------
		int ServerSocket::sendData(std::string _str) {
			// Echo the buffer back to the sender
			int iSendResult = send( mClientSocket, _str.c_str(), _str.size(), 0 );
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(mClientSocket);
				#if defined (_WIN32)
					WSACleanup();
				#endif
				return 1;
			}
			printf("Bytes sent: %d\n", iSendResult);
			
			return 0;
		}
		
		//-----------------------------------------------------------------------------
		std::string ServerSocket::receiveData() {
			char recvbuf[1024];
			int recvbuflen = 1024;

			int iResult = recv(mClientSocket, recvbuf, recvbuflen, 0);
			if (iResult < 0) {
				return "ERROR";
			}
			printf("Bytes received: %d\n", iResult);

			std::string msg;

			msg.append(recvbuf, iResult);

			return msg;
		}

		//-----------------------------------------------------------------------------
		int ServerSocket::listenClient(){
			int iResult = listen(mSocket, SOMAXCONN);
			if (iResult == SOCKET_ERROR) {
				printf("listen failed with error: %d\n", WSAGetLastError());
				closesocket(mSocket);
				#if defined (_WIN32)
					WSACleanup();
				#endif
				return 1;
			}

			return 0;
		}

		//-----------------------------------------------------------------------------
		int ServerSocket::acceptClient(){
			// Accept a client socket
			mClientSocket = accept(mSocket, NULL, NULL);
			if (mClientSocket == INVALID_SOCKET) {
				printf("accept failed with error: %d\n", WSAGetLastError());
				closesocket(mSocket);
				#if defined (_WIN32)
					WSACleanup();
				#endif
				
				return 1;
			}

			// No longer need server socket
			closesocket(mSocket);
			
			return 0;
		}

		//-----------------------------------------------------------------------------
		int ServerSocket::initializeSocket(){
			// Resolve the server address and port
			int iResult = getaddrinfo(NULL, mPort.c_str(), &mHints, &mResult);
			if ( iResult != 0 ) {
				printf("getaddrinfo failed with error: %d\n", iResult);
				#if defined (_WIN32)
					WSACleanup();
				#endif
				return 1;
			}

			// Create a SOCKET for connecting to server
			mSocket = socket(mResult->ai_family, mResult->ai_socktype, mResult->ai_protocol);
			if (mSocket == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				freeaddrinfo(mResult);
				#if defined (_WIN32)
					WSACleanup();
				#endif
				return 1;
			}

			return 0;
		}
		//-----------------------------------------------------------------------------
		int ServerSocket::connectSocket(){
			// Setup the TCP listening socket
			int iResult = bind( mSocket, mResult->ai_addr, (int)mResult->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				printf("bind failed with error: %d\n", WSAGetLastError());
				freeaddrinfo(mResult);
				closesocket(mSocket);
				#if defined (_WIN32)
					WSACleanup();
				#endif
				return 1;
			}

			freeaddrinfo(mResult);
			return 0;

		}
		//-----------------------------------------------------------------------------
		
		//-----------------------------------------------------------------------------
		
	}	//	namespace comm
}	//	namespace BOViL