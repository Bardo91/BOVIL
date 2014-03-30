/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-29
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_COMM_CLIENTSOCKET_H_
#define _BOVIL_CORE_COMM_CLIENTSOCKET_H_

#include "Socket.h"

namespace BOViL{
	namespace comm{
		//-----------------------------------------------------------------------------
		class ClientSocket: public Socket{
		private:
			ClientSocket(const std::string _ip, const std::string _port);
			~ClientSocket();

		private:
			addrinfo *mPtr;

			std::string mServerIp, mServerPort;
		};	//	class ClientSocket
		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_CORE_COMM_CLIENTSOCKET_H_