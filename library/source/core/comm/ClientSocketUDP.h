/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-05-31
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_CORE_COMM_CLIENTSOCKETUDP_H_
#define _BOVIL_CORE_COMM_CLIENTSOCKETUDP_H_

#include "SocketUDP.h"

namespace BOViL{
	namespace comm{
		class ClientSocketUDP : public SocketUDP{
		protected:
			ClientSocketUDP(const std::string &_serverIp, const std::string &_serverPort);

		private:
			std::string mServerIp, mServerPort;
			
			friend class Socket;	// 666 TODO: no se si es lo mejor
		};	//	class ClientSocketTCP
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_CORE_COMM_CLIENTSOCKETUDP_H_
