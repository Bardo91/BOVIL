/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-03-29
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_COMM_CLIENTSOCKET_H_
#define _BOVIL_CORE_COMM_CLIENTSOCKET_H_

#include "Sockets.h"

namespace BOViL{
	namespace comm{
		//-----------------------------------------------------------------------------
		template<eSocketType type_>
		class ClientSocket: public Socket{
		public:
			ClientSocket(const std::string _ip, const std::string _port);

		protected:
			int initializeSocket();
			int connectSocket();

			int closeSocket();

		private:
			addrinfo *mPtr;

			std::string mServerIp, mServerPort;
		};	//	class ClientSocket
		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL

#include "ClientSocket.inl"

#endif	// _BOVIL_CORE_COMM_CLIENTSOCKET_H_
