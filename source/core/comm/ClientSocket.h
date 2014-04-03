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
		class ClientSocket: public Socket{
		public:
			ClientSocket(const std::string _ip, const std::string _port);

			int sendData(std::string _data);
			std::string receiveData();

		protected:
			int initializeSocket();
			int connectSocket();

		private:
			addrinfo *mPtr;

			std::string mServerIp, mServerPort;
		};	//	class ClientSocket
		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_CORE_COMM_CLIENTSOCKET_H_
