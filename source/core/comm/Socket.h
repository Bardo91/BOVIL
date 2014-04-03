/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-30
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_COMM_SOCKET_H_
#define _BOVIL_CORE_COMM_SOCKET_H_

#include <string>

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
	#include <sys/sockets.h>
	#include <netdb.h>
			
#endif

namespace BOViL{
	namespace comm{
		class ClientSocket;
		class ServerSocket;

		class Socket{
		public:
			virtual int sendData(std::string _data) = 0;
			virtual std::string receiveData() = 0;

			int closeSocket();

		protected:		
			Socket()	{};
			virtual int initializeSocket() = 0;
			virtual int connectSocket() = 0;


		public:		// static members: Factory, etc.
			static ClientSocket* createClientSocket(std::string _ip, std::string _port);
			static ServerSocket* createServerSocket(std::string _port);

		protected:	
			#if defined(_WIN32)
				WSADATA mWsaData;
			#endif

			SOCKET mSocket;
			
			addrinfo *mResult, mHints;
		};	//	class Socket
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_CORE_COMM_SOCKET_H_