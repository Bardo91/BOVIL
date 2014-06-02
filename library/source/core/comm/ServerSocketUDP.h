/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-06-01
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_CORE_COMM_SERVERSOCKETUDP_H_
#define _BOVIL_CORE_COMM_SERVERSOCKETUDP_H_

#include "SocketUDP.h"

namespace BOViL{
	namespace comm{
		class ServerSocketUDP : public SocketUDP{
		protected:
			ServerSocketUDP(const std::string &_serverPort);

		private:
			std::string mServerPort;

			friend class Socket;	// 666 TODO: no se si es lo mejor
		};	//	class ServerSocketTCP

	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_CORE_COMM_SERVERSOCKETUDP_H_
