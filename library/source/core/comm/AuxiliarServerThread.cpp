/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-06
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "AuxiliarServerThread.h"

namespace BOViL {
	namespace comm {
		//-----------------------------------------------------------------------------
		AuxiliarServerThread::AuxiliarServerThread(SOCKET _socket): mIndex(0),
																	mThread(nullptr),
																	mSocket(_socket){

			startThread();

		}

		//-----------------------------------------------------------------------------
		AuxiliarServerThread::AuxiliarServerThread(SOCKET _socket, int _index) :	mIndex(_index),
																					mThread(nullptr),
																					mSocket(_socket){
			startThread();

		}
		
		//-----------------------------------------------------------------------------
		AuxiliarServerThread::AuxiliarServerThread(SOCKET _socket, int _index, AuxiliarServerThread **_threadList): 
										mThreadList(_threadList),
										mIndex(_index),
										mThread(nullptr),
										mSocket(_socket) {

			startThread();

		}

		//-----------------------------------------------------------------------------
		AuxiliarServerThread::~AuxiliarServerThread(){
			std::cout << "Closing connection: " << mIndex << std::endl;
			while(!stopThread());

			if(mThreadList[mIndex] == this){	// 777 Das good, but, in Server mNoConnections keep same size...
				mThreadList[mIndex] = nullptr;
			}
		}

		//-----------------------------------------------------------------------------
		bool AuxiliarServerThread::startThread(){
			if(mThread == nullptr){
				mIsRunning = true;

				mThread = new std::thread(&AuxiliarServerThread::watchFunction, this);
				
				return true;
			}else 
				return false;

		}

		//-----------------------------------------------------------------------------
		bool AuxiliarServerThread::stopThread(){
			if(mThread != nullptr && mThread->joinable()){
				mIsRunning = false;
				mThread->join();		// 666 TODO: be carefully, because it cant be join if recv in watchfunction keep waiting... searchc how to solve
				delete mThread;
				return true;
			} else 
				return false;

		}

		//-----------------------------------------------------------------------------
		bool AuxiliarServerThread::hasData(){
			std::mutex mutex;
			mutex.lock();
			int dataSize = mData.size();
			mutex.unlock();

			if(dataSize > 0){
				return true;
			}
			return false;

		}

		//-----------------------------------------------------------------------------
		std::vector<std::string> AuxiliarServerThread::readData(){
			std::mutex mutex;
			mutex.lock();
			std::vector<std::string> data = mData;
			mData.clear();
			mutex.unlock();

			return data;
		}

		//-----------------------------------------------------------------------------
		int AuxiliarServerThread::writeData(std::string _data){
			// Echo the buffer back to the sender
			int iSendResult = send( mSocket, _data.c_str(), _data.size(), 0 );
			if (iSendResult == SOCKET_ERROR) {
				return -1;
			}
			printf("Bytes sent: %d\n", iSendResult);
			
			return 0;
		}

		//-----------------------------------------------------------------------------
		void AuxiliarServerThread::watchFunction(){
			std::mutex mutex;

			while(mIsRunning){
				int recvbuflen = 4096;
				char recvbuf[4096];
				
				int iResult = recv(mSocket, recvbuf, recvbuflen, MSG_PARTIAL);
				if (iResult > 0) {
					std::cout << "Connection " << mIndex << " has received " << iResult << "bytes" << std::endl;

					std::string msg;

					msg.append(recvbuf, iResult);
					
					mutex.lock();
					mData.push_back(msg);
					mutex.unlock();
				} else if (iResult == SOCKET_ERROR){
					// Socket error, closing connection.
					mIsRunning = false;
				}
			}

			// Auxiliar thread has nothing to do if connection failed. Selfdestroy
			delete this;
		}

		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL