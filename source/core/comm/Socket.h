/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-30
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_COMM_SOCKET_H_
#define _BOVIL_CORE_COMM_SOCKET_H_

#include <string>

namespace BOViL{
	namespace comm{
		class Socket{
		public:
			virtual int sendData(std::string _data) = 0;
			virtual std::string receiveData() = 0;

			int closeSocket();

		protected:		
			Socket()	{};
			virtual int initializeSocket() = 0;
			virtual int connectSocket() = 0;


		public:		// static members: Factory, etc.
			static Socket* createClientSocket(std::string _ip, std::string _port);
			static Socket* createServerSocket(std::string _port);

		protected:	
			WSADATA mWsaData;
			SOCKET mSocket;

			addrinfo *mResult, mHints;
		};	//	class Socket
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_CORE_COMM_SOCKET_H_