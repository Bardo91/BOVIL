/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-03-27
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_COMM_SERVERSOCKET_H_
#define _BOVIL_CORE_COMM_SERVERSOCKET_H_

#include "Socket.h"

namespace BOViL{
	namespace comm{
		//-----------------------------------------------------------------------------
		class ServerSocket: public Socket{
		public:
			int sendData(std::string _data);
			std::string receiveData();

			int listenClient();
			int acceptClient();

		private:
			ServerSocket(const std::string _port);
			~ServerSocket();

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

#endif	// _BOVIL_CORE_COMM_SERVERSOCKET_H_