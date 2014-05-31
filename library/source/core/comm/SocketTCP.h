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

namespace BOVil{
	namespace comm{
		class SocketTCP : public Socket{
		public:
			bool sendMsg(std::string _msg);
			bool receiveMsg(std::string &_msg);
		protected:
			SocketTCP() {};
		};
	}
}


#endif // _BOVIL_CORE_COMM_SOCKETUDP_H_