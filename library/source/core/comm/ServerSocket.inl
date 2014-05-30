/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-03-27
//
/////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>
#include <sstream>

namespace BOViL{
	namespace comm{
		//-----------------------------------------------------------------------------
		template<eSocketType type_>
		ServerSocket<type_>::ServerSocket(const std::string _port){
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
			mHints.ai_socktype = type_;
			mHints.ai_protocol = 0; // IPPROTO_UDP; IPPROTO_TCP;
			mHints.ai_flags = AI_PASSIVE;

			iResult += initializeSocket();
			iResult += connectSocket();

			assert(!iResult);	// If errors break!

		}

		//-----------------------------------------------------------------------------
		template<eSocketType type_>
		int ServerSocket<type_>::listenClient(){
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
		template<eSocketType type_>
		SOCKET ServerSocket<type_>::acceptClient(){
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
		template<eSocketType type_>
		int ServerSocket<type_>::initializeSocket(){
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
		template<eSocketType type_>
		int ServerSocket<type_>::connectSocket(){
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
		template<eSocketType type_>
		int ServerSocket<type_>::closeSocket(){
			closesocket(mSocketOut);
			closesocket(mSocketOwn);

			return 0;
		}
		//-----------------------------------------------------------------------------
		
	}	//	namespace comm
}	//	namespace BOViL
