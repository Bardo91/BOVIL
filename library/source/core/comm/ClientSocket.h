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
		template<int type_>
		class ClientSocket: public Socket<type_>{
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

#endif	// _BOVIL_CORE_COMM_CLIENTSOCKET_H_
