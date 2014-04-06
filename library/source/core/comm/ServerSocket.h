/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-03-27
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_COMM_SERVERSOCKET_H_
#define _BOVIL_CORE_COMM_SERVERSOCKET_H_

#include "Sockets.h"

namespace BOViL{
	namespace comm{
		//-----------------------------------------------------------------------------
		class ServerSocket: public Socket{
		public:
			ServerSocket();
			ServerSocket(const std::string _port);

			int listenClient();
			SOCKET acceptClient();

		protected:
			int initializeSocket();
			int connectSocket();
			
			int closeSocket();

		private:
			SOCKET mSocketOwn;

			std::string mPort;
		};	//	class ServerSocket
		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_CORE_COMM_SERVERSOCKET_H_
