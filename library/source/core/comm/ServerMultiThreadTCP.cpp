/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-06-01
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ServerMultiThreadTCP.h"
#include <mutex>

namespace BOViL{
	namespace comm {
		//-------------------------------------------------------------------------------
		//-------------------------- AuxiliarServerThread -------------------------------
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
		bool AuxiliarServerThread::readMsgs(std::vector<std::string> _messages){
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
				mThread->join();		// 666 TODO: be carefully, because it cant be join if recv in watchfunction keep waiting... searchc how to solve
				delete mThread;
				return true;
			}
			else
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
		void AuxiliarServerThread::watchFunction(){
			std::mutex mutex;

			while (mIsRunning){
				int recvbuflen = 4096;
				char recvbuf[4096];

				int iResult = recv(mSocket, recvbuf, recvbuflen, MSG_PARTIAL);
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

			// Auxiliar thread has nothing to do if connection failed. Selfdestroy
			delete this;
		}

		//-------------------------------------------------------------------------------
		//-------------------------- ServerMultiThreadTCP -------------------------------
		//-------------------------------------------------------------------------------
		ServerMultiThreadTCP::ServerMultiThreadTCP(std::string _serverPort): mServerPort(_serverPort) {

		}
		//-------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL
