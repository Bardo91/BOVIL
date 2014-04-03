/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-30
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "Socket.h"

#include "ClientSocket.h"
#include "ServerSocket.h"

namespace BOViL	{
	namespace comm{
		//-----------------------------------------------------------------------------
		ClientSocket* Socket::createClientSocket(std::string _ip, std::string _port){
			return new ClientSocket(_ip, _port);
		}
		//-----------------------------------------------------------------------------
		ServerSocket* Socket::createServerSocket(std::string _port){
			return new ServerSocket(_port);
		
		}
		//-----------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL