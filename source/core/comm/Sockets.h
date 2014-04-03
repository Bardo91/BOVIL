/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-03-30
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_COMM_SOCKET_H_
#define _BOVIL_CORE_COMM_SOCKET_H_

#include <string>
#include <cstring>
#include <iostream>

#if defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN

	#include <windows.h>
	#include <winsock2.h>
	#include <ws2tcpip.h>

	#pragma comment (lib, "Ws2_32.lib")
	#pragma comment (lib, "Mswsock.lib")
	#pragma comment (lib, "AdvApi32.lib")
#endif

#if defined(__linux__)
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>

	typedef int SOCKET;
	const int INVALID_SOCKET = -1;
	const int SOCKET_ERROR = -1;

	#define closesocket(SOCKET) close(SOCKET)
#endif

namespace BOViL{
	namespace comm{
		class ClientSocket;
		class ServerSocket;

		class Socket{
		public:
			int sendData(std::string _data);
			std::string receiveData();

		protected:		
			Socket()	{};
			virtual int initializeSocket() = 0;
			virtual int connectSocket() = 0;

			virtual int closeSocket() = 0;

		public:		// static members: Factory, etc.
			static ClientSocket* createClientSocket(std::string _ip, std::string _port);
			static ServerSocket* createServerSocket(std::string _port);

		protected:	
			#if defined(_WIN32)
				WSADATA mWsaData;
			#endif

			SOCKET mSocketOut;
			
			addrinfo *mResult, mHints;
		};	//	class Socket
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_CORE_COMM_SOCKET_H_
