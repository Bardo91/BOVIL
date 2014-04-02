/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-27
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_COMM_SODEPS_WIN32_SERVERSOCKETWIN32_H_
#define _BOVIL_CORE_COMM_SODEPS_WIN32_SERVERSOCKETWIN32_H_

#if defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN

	#include <windows.h>
	#include <winsock2.h>
	#include <ws2tcpip.h>

	#pragma comment (lib, "Ws2_32.lib")
	#pragma comment (lib, "Mswsock.lib")
	#pragma comment (lib, "AdvApi32.lib")
#endif

#include "../../Socket.h"

namespace BOViL{
	namespace comm{
		//-----------------------------------------------------------------------------
		class ServerSocket: public Socket{
		public:
			ServerSocket(const std::string _port);

			int sendData(std::string _data);
			std::string receiveData();

			int listenClient();
			int acceptClient();

		protected:
			int initializeSocket();
			int connectSocket();
			
		private:
			SOCKET mClientSocket;

			std::string mPort;
		};	//	class ServerSocket
		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_CORE_COMM_SODEPS_WIN32_SERVERSOCKETWIN32_H_