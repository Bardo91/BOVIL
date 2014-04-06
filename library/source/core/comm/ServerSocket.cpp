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
		ServerSocket::ServerSocket(){

		}

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
			mHints.ai_family = AF_INET;
			mHints.ai_socktype = SOCK_STREAM;
			mHints.ai_protocol = 0;//IPPROTO_TCP;
			mHints.ai_flags = AI_PASSIVE;

			iResult += initializeSocket();
			iResult += connectSocket();

			assert(!iResult);	// If errors break!

		}

		//-----------------------------------------------------------------------------
		int ServerSocket::listenClient(){
			int iResult = listen(mSocketOwn, SOMAXCONN);
			if (iResult == SOCKET_ERROR) {
				std::cout << "listen failed with error: " << getLastError() << std::endl;
				closeSocket();

				return 1;
			}
			std::cout << "Start listening the port." << std::endl;
			return 0;
		}

		//-----------------------------------------------------------------------------
		SOCKET ServerSocket::acceptClient(){
			// Accept a client socket
			std::cout << "Waiting client to accept connection";
			mSocketOut = accept(mSocketOwn, NULL, NULL);
			if (mSocketOut == INVALID_SOCKET) {
				std::cout << "Accept failed. Error was: " << getLastError() << std::endl;

				closeSocket();				
				return 0;
			}

			std::cout << "----> Client accepted" << std::endl;
			
			return mSocketOut;
		}

		//-----------------------------------------------------------------------------
		int ServerSocket::initializeSocket(){
			// Resolve the server address and port
			std::cout << "Getting address info";
			int iResult = getaddrinfo(NULL, mPort.c_str(), &mHints, &mResult);
			if ( iResult != 0 ) {
				std::cout << "getaddrinfo failed with error: " << iResult << std::endl;
				#if defined (_WIN32)
					WSACleanup();
				#endif
				return 1;
			}
			std::cout << "----> Got address info" << std::endl;

			// Create a SOCKET for connecting to server
			std::cout << "Creating server socket";
			mSocketOwn = socket(mResult->ai_family, mResult->ai_socktype, mResult->ai_protocol);
			if (mSocketOwn == INVALID_SOCKET) {
				std::cout << "Socket failed. Error was: " << getLastError() << std::endl;
				freeaddrinfo(mResult);
				return 1;
			}
			std::cout << "----> Socket created" << std::endl;

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
			#ifdef _WIN32
				bool bOptVal = TRUE;
				int bOptLen = sizeof(bool);
				iResult = setsockopt(mSocketOwn, SOL_SOCKET, SO_REUSEADDR, (char *) bOptVal, bOptLen);
			#endif

			std::cout << "Binding to port";
			iResult = bind( mSocketOwn, mResult->ai_addr, mResult->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				std::cout << "Bind failed" << std::endl;
				std::cout << "Error was: " << getLastError() << std::endl;
				freeaddrinfo(mResult);
				closeSocket();
				return 1;
			}
			std::cout << "----> Binded to port" << std::endl;

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
