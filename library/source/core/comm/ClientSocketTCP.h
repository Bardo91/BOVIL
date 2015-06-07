/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-05-31
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_CORE_COMM_CLIENTSOCKETTCP_H_
#define _BOVIL_CORE_COMM_CLIENTSOCKETTCP_H_

#include "SocketTCP.h"

namespace BOViL{
	namespace comm{
		/** Class that defines a TCP clients socket construction.
		*/
		class ClientSocketTCP: public SocketTCP{
		protected:
			ClientSocketTCP(const std::string &_serverIp, const std::string &_serverPort);

		private:
			std::string mServerIp, mServerPort;
			addrinfo *mPtr, *mResults;

			friend class Socket;	// 666 TODO: no se si es lo mejor
		};	//	class ClientSocketTCP
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_CORE_COMM_CLIENTSOCKETTCP_H_
