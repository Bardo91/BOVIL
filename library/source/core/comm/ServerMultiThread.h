/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-06
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_CORE_COMM_SERVERMULTITHREAD_H_
#define _BOVIL_CORE_COMM_SERVERMULTITHREAD_H_

#include "AuxiliarServerThread.h"
#include "ServerSocket.h"

#include <thread>

namespace BOViL{
	namespace comm{

		const int MAXCONNECTIONS = 128;

		class ServerMultiThread{
		public:		// public interface
			ServerMultiThread(std::string _PORT);
			~ServerMultiThread();

			int getNoConnections();
			AuxiliarServerThread* getThread(int _threadNo);

		private:	// server members
			ServerSocket mServerSocket;

			std::thread mAcceptThread;

			int mNoConnections;
			AuxiliarServerThread* mThreadList[MAXCONNECTIONS];	// 777 TODO: Possible improvement. Design a container as chained list.
		
		private: //	Thread function
			void acceptFunction();
		
		};	//	class ServerMultiThread
	}	//	namespace comm
}	//	namespace BOViL

#endif	//	_BOVIL_CORE_COMM_SERVERMULTITHREAD_H_