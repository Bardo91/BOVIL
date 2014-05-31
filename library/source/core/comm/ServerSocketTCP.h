/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-05-31
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_CORE_COMM_SERVERSOCKETTCP_H_
#define _BOVIL_CORE_COMM_SERVERSOCKETTCP_H_

#include "SocketTCP.h"

namespace BOViL{
	namespace comm{
		class ServerSocketTCP : public SocketTCP{
			SOCKET acceptClient();
		protected:
			ServerSocketTCP(const std::string &_serverPort);

		private:
			std::string mServerPort;
			addrinfo *mResult;

			friend class Socket;	// 666 TODO: no se si es lo mejor
		};	//	class ServerSocketTCP

	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_CORE_COMM_SERVERSOCKETTCP_H_
