/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:			Pablo Ramon Soria
//			Date:			2014-03-30
//			Last Update:	2014-05-31
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_CORE_COMM_SOCKET_H_
#define _BOVIL_CORE_COMM_SOCKET_H_

#include <string>
#include <cstring>
#include <iostream>

//---------------------------------------------------------------------------------------
//-------------------------------- OS DEPENDENCIES --------------------------------------
//---------------------------------------------------------------------------------------
#if defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN

	#include <Windows.h>
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
	#include <netdb.h>

	typedef int SOCKET;
	const int INVALID_SOCKET = -1;
	const int SOCKET_ERROR = -1;

	#define closesocket(SOCKET) close(SOCKET)
#endif

//---------------------------------------------------------------------------------------
//-------------------------------- Socket Interface -------------------------------------
//---------------------------------------------------------------------------------------
namespace BOViL{
	namespace comm{
		enum class eSocketType {serverTCP, clientTCP, serverUDP, clientUDP};
		
		class Socket{
		public:
			virtual bool sendMsg(std::string _msg) = 0;
			virtual bool receiveMsg(std::string &_msg) = 0;

		public:	// Socket factory
			static Socket* createSocket(const eSocketType _socketType, const std::string &_serverPort, const std::string &_serverIp = "");
		protected:
			Socket();

			bool closeSocket();

			int getLastError();

		protected:
			#if defined(_WIN32)
				WSADATA mWsaData;
			#endif

			SOCKET mSocket;

			addrinfo mHints;
		};	//	class Socket
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_CORE_COMM_SOCKET_H_
