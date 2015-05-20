/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-05-31
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_CORE_COMM_SOCKETTCP_H_
#define _BOVIL_CORE_COMM_SOCKETTCP_H_

#include "Socket.h"

namespace BOViL{
	namespace comm{
		class SocketTCP : public Socket{
		public:
			int sendMsg(const unsigned char *_buffer, const unsigned _bufferSize);
			int receiveMsg(unsigned char *_buffer, const unsigned _bufferSize);
		
		protected:
			SocketTCP() {};

		};	//	class SocketTCP
	}
}


#endif // _BOVIL_CORE_COMM_SOCKETUDP_H_