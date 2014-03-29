/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-27
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_COMM_SERVERSOCKET_H_
#define _BOVIL_CORE_COMM_SERVERSOCKET_H_

#if defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN

	#include <windows.h>
	#include <winsock2.h>
	#include <ws2tcpip.h>

	#pragma comment (lib, "Ws2_32.lib")
#endif

#if defined(__linux__)
	#include <sys/types.h>
	#include <sys/socket.h>
#endif

#include <string>

namespace BOViL{
	namespace comm{
		//-----------------------------------------------------------------------------
		class ServerSocket{
		public:
			ServerSocket();

			int initializeSocket(std::string& _port);
			int acceptClient();
			void closeSocket();

			std::string receiveStr();
			int sendStr(std::string& _str);
		private:
			WSADATA mWsaData;
			SOCKET mServerSocket;
			SOCKET mClientSocket;

			addrinfo *mResult, mHints;
		};	//	class ServerSocket
		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_CORE_COMM_SERVERSOCKET_H_