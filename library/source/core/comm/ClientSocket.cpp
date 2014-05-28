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
		template<int type_>
		ClientSocket<type_>::ClientSocket(const std::string _ip, const std::string _port){
			mServerIp = _ip;
			mServerPort = _port;
			mSocketOut = INVALID_SOCKET;
			mResult = nullptr;
			mPtr = nullptr;

			int iResult = 0;

			#if defined (_WIN32)
				// Initialize Winsock
				iResult = WSAStartup(MAKEWORD(2,2), &mWsaData);
				if (iResult != 0) {
					printf("WSAStartup failed with error: %d\n", iResult);
					assert(false);
				}
			#endif

			memset( &mHints, 0, sizeof(mHints));
			mHints.ai_family = AF_INET;
			
			mHints.ai_socktype = type_; // Templated protocol

			mHints.ai_protocol = 0;

			iResult += initializeSocket();
			iResult += connectSocket();

			assert(!iResult);	// If errors break!

		}

		//-----------------------------------------------------------------------------
		template<int type_>
		int ClientSocket<type_>::initializeSocket(){
			// Resolve the server address and port
			std::cout << "Getting address info";
			int iResult = getaddrinfo(mServerIp.c_str(), mServerPort.c_str(), &mHints, &mResult);
			if ( iResult != 0 ) {
				std::cout << "etaddrinfo failed with error: " << getLastError() << std::endl;
				#if defined (_WIN32)
					WSACleanup();
				#endif
				return 1;
			}
			std::cout << "----> Got address info" << std::endl;
			return 0;
		}
		//-----------------------------------------------------------------------------
		template<int type_>
		int ClientSocket<type_>::connectSocket(){
			// Attempt to connect to an address until one succeeds
			for(mPtr=mResult; mPtr != NULL ;mPtr=mPtr->ai_next) {

				// Create a SOCKET for connecting to server
				std::cout << "Creating client Socket";
				mSocketOut = socket(mPtr->ai_family, mPtr->ai_socktype, mPtr->ai_protocol);
				if (mSocketOut == INVALID_SOCKET) {
					std::cout << "Socket Error with error: " << getLastError() << std::endl;

					return 1;
				}
				std::cout << "----> Socket created" << std::endl;

				// Connect to server.
				std::cout << "Connecting to socket";
				int iResult = connect( mSocketOut, mPtr->ai_addr, (int) mPtr->ai_addrlen);
				if (iResult == SOCKET_ERROR) {
					closeSocket();
					mSocketOut = INVALID_SOCKET;
					std::cout << "Socket Error with error: " << getLastError() << std::endl;
					continue;
				}
				std::cout << "----> Connected to socket" << std::endl;

				break;
			}

			freeaddrinfo(mResult);

			if (mSocketOut == INVALID_SOCKET) {
				printf("Unable to connect to server!\n");
				#if defined (_WIN32)
					WSACleanup();
				#endif
				return 1;
			}

			return 0;
		}
		//-----------------------------------------------------------------------------
		template<int type_>
		int ClientSocket<type_>::closeSocket(){
			closesocket(mSocketOut);

			return 0;
		}

		//-----------------------------------------------------------------------------
		
	}	//	namespace comm
}	//	namespace BOViL
