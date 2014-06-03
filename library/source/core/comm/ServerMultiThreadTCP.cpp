/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-06-01
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ServerMultiThreadTCP.h"

#include <mutex>
#include <cassert>

namespace BOViL{
	namespace comm {
		//-------------------------------------------------------------------------------
		//-------------------------- AuxiliarServerThread -------------------------------
		//-------------------------------------------------------------------------------
		AuxiliarServerThread::~AuxiliarServerThread(){
			while (!closeConnection());

		}

		//-------------------------------------------------------------------------------
		bool AuxiliarServerThread::sendMsg(const std::string &_msg){
			if (send(mSocket, _msg.c_str(), _msg.size(), 0) == SOCKET_ERROR)
				return false;
			return true;
		}
		//-------------------------------------------------------------------------------
		bool AuxiliarServerThread::hasMsg(){
			std::mutex mutex;
			mutex.lock();
			int dataSize = mMessages.size();
			mutex.unlock();

			if (dataSize > 0)
				return true;
			return false;

		}
		//-----------------------------------------------------------------------------
		bool AuxiliarServerThread::readMsgs(std::vector<std::string> &_messages){
			
			if (!hasMsg())
				return false;

			std::mutex mutex;
			mutex.lock();
			_messages = mMessages;
			mMessages.clear();
			mutex.unlock();

			return true;
		}


		//-------------------------------------------------------------------------------
		bool AuxiliarServerThread::startThread(){
			if (mThread == nullptr){
				mIsRunning = true;

				mThread = new std::thread(&AuxiliarServerThread::watchFunction, this);

				return true;
			}
			else
				return false;

		}

		//-----------------------------------------------------------------------------
		bool AuxiliarServerThread::stopThread(){
			if (mThread != nullptr && mThread->joinable()){
				mIsRunning = false;
				mThread->join();		// 666 TODO: be carefully, because it cant be join if recv in watchfunction keep waiting... search how to solve
				return true;
			} else
				return false;

		}

		//-------------------------------------------------------------------------------
		bool AuxiliarServerThread::closeConnection(){
			int tries = 0;
			do{
				tries++;
				if (tries == 100)
					return false;
			}
			while (tries <= 100 && !stopThread());

			if (*mMySelf == this)	// 777 make a revision
				*mMySelf = nullptr;
			
			return true;
		}		
		
		//-------------------------------------------------------------------------------
		AuxiliarServerThread::AuxiliarServerThread(SOCKET _socket, AuxiliarServerThread **_mySelf) : mMySelf(_mySelf), mSocket(_socket) {
			startThread();
		}

		//-------------------------------------------------------------------------------
		void AuxiliarServerThread::watchFunction(){
			std::mutex mutex;

			while (mIsRunning){
				int recvbuflen = 4096;
				char recvbuf[4096];

				int iResult = recv(mSocket, recvbuf, recvbuflen, 0); // 666 TODO: MSG_PARTIAL);
				if (iResult > 0) {
					//std::cout << "Connection " << mIndex << " has received " << iResult << "bytes" << std::endl;

					std::string msg;

					msg.append(recvbuf, iResult);

					mutex.lock();
					mMessages.push_back(msg);
					mutex.unlock();
				}
				else if (iResult == SOCKET_ERROR){
					// Socket error, closing connection.
					mIsRunning = false;
				}
			}
		}

		//-------------------------------------------------------------------------------
		//-------------------------- ServerMultiThreadTCP -------------------------------
		//-------------------------------------------------------------------------------
		ServerMultiThreadTCP::ServerMultiThreadTCP(std::string _serverPort):	mServerPort(_serverPort), 
																				mIsRunning(true), 
																				mAcceptSocket(INVALID_SOCKET),
																				mNoConnections(0) {

			// Initialization of accept socket
			#if defined (_WIN32) 
				// Initialize Winsock
				if (WSAStartup(MAKEWORD(2, 2), &mWsaData) != 0) {
					assert(false);
				}
			#endif

			addrinfo mHints, *mResult;

			memset(&mHints, 0, sizeof(mHints));
			mHints.ai_family = AF_INET;
			mHints.ai_socktype = SOCK_STREAM;
			mHints.ai_protocol = IPPROTO_TCP;
			mHints.ai_flags = AI_PASSIVE;

			// Resolve the server address and port
			if (getaddrinfo(NULL, mServerPort.c_str(), &mHints, &mResult) != 0) {
				assert(false);
			}

			// Create a SOCKET for connecting to server
			mAcceptSocket = socket(mResult->ai_family, mResult->ai_socktype, mResult->ai_protocol);
			if (mAcceptSocket == INVALID_SOCKET) {
				closesocket(mAcceptSocket);
				freeaddrinfo(mResult);
				assert(false);
			}

			// Setup the TCP listening socket
			#ifdef __linux__
				int yes = 1;
				setsockopt(mAcceptSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
			#endif
			#ifdef _WIN32
				bool bOptVal = TRUE;
				int bOptLen = sizeof(bool);
				setsockopt(mAcceptSocket, SOL_SOCKET, SO_REUSEADDR, (char *)bOptVal, bOptLen);
			#endif

			if (bind(mAcceptSocket, mResult->ai_addr, mResult->ai_addrlen) == SOCKET_ERROR) {
				freeaddrinfo(mResult);
				closesocket(mAcceptSocket);
				assert(false);
			}

			if (listen(mAcceptSocket, SOMAXCONN) == SOCKET_ERROR) {
				closesocket(mAcceptSocket);
				assert(false);
			}

			freeaddrinfo(mResult);

			// Start accept thread
			mAcceptThread = std::thread(&ServerMultiThreadTCP::acceptFunction, this);
		}

		//-------------------------------------------------------------------------------
		bool ServerMultiThreadTCP::sendMsgTo(const std::string &_msg, int _connection){
			return mThreadList[_connection]->sendMsg(_msg);
		}
		
		//-------------------------------------------------------------------------------
		bool ServerMultiThreadTCP::readMsgsFrom(std::vector<std::string> &_msgs, int _connection){
			if (mThreadList[_connection] == nullptr)
				return false;

			return mThreadList[_connection]->readMsgs(_msgs);
		}

		
		//-------------------------------------------------------------------------------
		int ServerMultiThreadTCP::requestNoConnections(){
			return mNoConnections;
		}

		//-------------------------------------------------------------------------------
		void ServerMultiThreadTCP::acceptFunction(){
			while (mIsRunning){
				SOCKET conn = accept(mAcceptSocket, nullptr, nullptr);
				if (conn == INVALID_SOCKET) {
					closesocket(mAcceptSocket);
					assert(false);
				}
				if (conn != 0 && mNoConnections < MAX_CONNECTIONS){
					mThreadList[mNoConnections] = new AuxiliarServerThread(conn, &mThreadList[mNoConnections]);
					mNoConnections++;
				}
			}
		}	
		//-------------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL
