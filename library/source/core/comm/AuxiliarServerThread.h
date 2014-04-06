/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-06
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_COMM_SERVERAUXILIARTHREAD_H_
#define _BOVIL_CORE_COMM_SERVERAUXILIARTHREAD_H_

#include "Sockets.h"

#include <functional>
#include <thread>

namespace BOViL{
	namespace comm{
		class AuxiliarServerThread: std::thread {
		public:
			AuxiliarServerThread(SOCKET _socket);
			AuxiliarServerThread(SOCKET _socket, std::function<void (...)> _function, ...);

		private:	// Thread's function
			void stdAuxiliarServerFunction();
		};
	}	//	namespace comm
}	//	namespace BOViL

#endif	//	_BOVIL_CORE_COMM_SERVERAUXILIARTHREAD_H_