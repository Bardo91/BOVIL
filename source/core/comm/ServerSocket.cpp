/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-03-27
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ServerSocket.h"

#include <cassert>
#include <iostream>
#include <sstream>

namespace BOViL{
	namespace comm{
				//-----------------------------------------------------------------------------
		ServerSocket::ServerSocket(const std::string _port){
			mPort = _port;
			mSocketOwn = INVALID_SOCKET;
			mSocketOut = INVALID_SOCKET;
			mResult = nullptr;

			int iResult = 0;

			#if defined (_WIN32)
				// Initialize Winsock
				iResult = WSAStartup(MAKEWORD(2,2), &mWsaData);
				if (iResult != 0) {
					printf("WSAStartup failed with error: %d\n", iResult);
					assert(false);
				}
			#endif

			memset(&mHints, 0, sizeof(mHints));
			mHints.ai_family = AF_UNSPEC;//AF_INET;
			mHints.ai_socktype = SOCK_STREAM;
			//mHints.ai_protocol = IPPROTO_TCP;
			mHints.ai_flags = AI_PASSIVE;

			iResult += initializeSocket();
			iResult += connectSocket();

			assert(!iResult);	// If errors break!

		}

		//-----------------------------------------------------------------------------
		int ServerSocket::listenClient(){
			int iResult = listen(mSocketOwn, SOMAXCONN);
			if (iResult == SOCKET_ERROR) {
				std::cout << "listen failed with error" << std::endl;

				closeSocket();
				#if defined (_WIN32)
					std::cout << "Error was: " << WSAGetLastError() << std::endl;
					WSACleanup();
				#endif
				return 1;
			}

			return 0;
		}

		//-----------------------------------------------------------------------------
		int ServerSocket::acceptClient(){
			// Accept a client socket
			mSocketOut = accept(mSocketOwn, NULL, NULL);
			if (mSocketOut == INVALID_SOCKET) {
				std::cout << "Accept failed." << std::endl;

				closeSocket();
				#if defined (_WIN32)
					std::cout << "Error was: " << WSAGetLastError() << std::endl;
					WSACleanup();
				#endif
				
				return 1;
			}
			
			return 0;
		}

		//-----------------------------------------------------------------------------
		int ServerSocket::initializeSocket(){
			// Resolve the server address and port
			int iResult = getaddrinfo(NULL, mPort.c_str(), &mHints, &mResult);
			if ( iResult != 0 ) {
				std::cout << "getaddrinfo failed with error: " << iResult << std::endl;
				#if defined (_WIN32)
					WSACleanup();
				#endif
				return 1;
			}

			// Create a SOCKET for connecting to server
			mSocketOwn = socket(mResult->ai_family, mResult->ai_socktype, mResult->ai_protocol);
			if (mSocketOwn == INVALID_SOCKET) {
				std::cout << "Socket failed." << std::endl;
				freeaddrinfo(mResult);
				#if defined (_WIN32)
					std::cout << "Error was: " << WSAGetLastError() << std::endl;
					WSACleanup();
				#endif
				return 1;
			}

			return 0;
		}
		//-----------------------------------------------------------------------------
		int ServerSocket::connectSocket(){
			// Setup the TCP listening socket
			int iResult = 0;
			#ifdef __linux__
				int yes = 1;
				iResult = setsockopt(mSocketOwn, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
			#endif

			iResult = bind( mSocketOwn, mResult->ai_addr, mResult->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				std::cout << "Bind failed" << std::endl;
				std::cout << "Error was: " << errno << std::endl;
				freeaddrinfo(mResult);
				closeSocket();
				#if defined (_WIN32)
					std::cout << "Error was: " << WSAGetLastError() << std::endl;
					WSACleanup();
				#endif
				return 1;
			}

			freeaddrinfo(mResult);
			return 0;

		}
		//-----------------------------------------------------------------------------
		int ServerSocket::closeSocket(){
			closesocket(mSocketOut);
			closesocket(mSocketOwn);

			return 0;
		}
		//-----------------------------------------------------------------------------
		
	}	//	namespace comm
}	//	namespace BOViL
