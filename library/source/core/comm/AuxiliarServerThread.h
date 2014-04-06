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
#include <string>
#include <thread>
#include <vector>

namespace BOViL{
	namespace comm{
		class AuxiliarServerThread: std::thread {
		public:	// public interface
			AuxiliarServerThread(SOCKET _socket);

			int startThread();
			int stopThread();
			
			bool hasData();
			std::string readData();
			int writeData(std::string _data);


		private:	// private members
			std::thread mThread;
			bool mIsRunning;	// Flag to know if current thread is running
			
			SOCKET mSocket;

			char *mInputBuffer;
			std::vector<std::string> mData;


		private:	//	thread private interdace

			void watchFunction();

		};
	}	//	namespace comm
}	//	namespace BOViL

#endif	//	_BOVIL_CORE_COMM_SERVERAUXILIARTHREAD_H_