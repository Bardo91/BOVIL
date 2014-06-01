/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-06-01
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_COMM_SERVERMULTITHREADTCP_H_
#define _BOVIL_CORE_COMM_SERVERMULTITHREADTCP_H_

#include "Socket.h"

#include <vector>
#include <thread>

const int MAX_CONNECTIONS = 128;

namespace BOViL{
	namespace comm {
		//-------------------------------------------------------------------------------
		// Forward declaration of ServerMultiThreadClass
		class ServerMultiThreadTCP;

		//-------------------------------------------------------------------------------
		class AuxiliarServerThread{
		public:
			bool sendMsg(const std::string &_msg);

			bool hasMsg();
			bool readMsgs(std::vector<std::string> _messages);

			bool startThread();
			bool stopThread();
			bool closeConnection();
		protected:
			AuxiliarServerThread::AuxiliarServerThread(SOCKET _socket, AuxiliarServerThread **_mySelf) : mSocket(_socket), mMySelf(_mySelf) {};

		private:
			AuxiliarServerThread **mMySelf;
			SOCKET mSocket;

			bool mIsRunning;
			std::vector<std::string> mMessages;
			
			std::thread *mThread;

			friend class ServerMultiThreadTCP;
		private:
			void watchFunction();
		};
		
		//-------------------------------------------------------------------------------
		class ServerMultiThreadTCP{
		public:
			ServerMultiThreadTCP(std::string _serverPort);

			bool sendMsgTo(const std::string &_msg, int _connection);
			bool readMsgFrom(std::string &_msg, int _connection);

			int requestNoConnections();

		private:
			std::string mServerPort;

			std::thread mAcceptThread;
			SOCKET mAcceptSocket;

			int mNoConnections;
			AuxiliarServerThread mThreadList[MAX_CONNECTIONS];

		private:
			void acceptFunction();
		};
	}	//	namespace comm
}	//	namespace BOViL


#endif	//	_BOVIL_CORE_COMM_SERVERMULTITHREADTCP_H_