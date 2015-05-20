/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-05-31
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_CORE_COMM_SOCKETUDP_H_
#define _BOVIL_CORE_COMM_SOCKETUDP_H_

#include "Socket.h"

namespace BOViL{
	namespace comm{
		class SocketUDP : public Socket{
		public:
			int sendMsg(const unsigned char *_buffer, const unsigned _bufferSize);
			int receiveMsg(unsigned char *_buffer, const unsigned _bufferSize);

		protected:
			SocketUDP() {};

			sockaddr_in mAddr;
		};	// class SocketUDP
	}
}


#endif // _BOVIL_CORE_COMM_SOCKETUDP_H_