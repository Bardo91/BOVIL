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
		/** Definition of supported socket types
		*/
		enum class eSocketType {serverTCP, clientTCP, serverUDP, clientUDP};
		
		/** Base socket class to generalize socket's use.
		*/
		class Socket{
		public:
			/** \brief abstract method to send messages throught socket.
			*	@param _buffer: buffer array that contains message to be sended.
			*	@param _bufferSize:	size message.
			*/
			virtual int sendMsg(const unsigned char *_buffer, const unsigned _bufferSize) = 0;

			/** \brief read message from socket.
			*	@param _buffer: buffer to store received message.
			*	@param _bufferSize: max size of buffer.
			*/
			virtual int receiveMsg(unsigned char *_buffer, const unsigned _bufferSize) = 0;

			/** \brief retreive socket descriptor to be used outside the class.
			*/
			SOCKET getSocketDescriptor(){ return mSocket; }

			bool closeSocket();

		public:	// Socket factory
			/** \brief static method to create a new socket
			*	@param _socketType: one of supported socket type
			*	@param _serverPort: desired port to be opened or server's port to be connected
			*	@param _serverIp: if connecting to socket, server's ip. localhost by default.
			*/
			static Socket* createSocket(const eSocketType _socketType, const std::string &_port, const std::string &_serverIp = "");
		protected:
			Socket();

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
