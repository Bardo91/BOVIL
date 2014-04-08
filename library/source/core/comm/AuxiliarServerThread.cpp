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
		AuxiliarServerThread::AuxiliarServerThread(SOCKET _socket, int _index) :	mIndex(0),
																					mThread(nullptr),
																					mSocket(_socket){
			startThread();

		}
		
		//-----------------------------------------------------------------------------
		AuxiliarServerThread::AuxiliarServerThread(SOCKET _socket, int _index, AuxiliarServerThread **_threadList): 
										mThreadList(_threadList),
										mIndex(0),
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
				mThread = new std::thread(&AuxiliarServerThread::watchFunction, this);

				mIsRunning = true;

				return true;
			}else 
				return false;

		}

		//-----------------------------------------------------------------------------
		bool AuxiliarServerThread::stopThread(){
			if(mThread != nullptr && mThread->joinable()){
				mThread->detach();
				delete mThread;
				mIsRunning = false;
				return true;
			} else 
				return false;

		}

		//-----------------------------------------------------------------------------
		bool AuxiliarServerThread::hasData(){
			if(mData.size() > 0){
				return true;
			}
			return false;

		}

		//-----------------------------------------------------------------------------
		std::vector<std::string> AuxiliarServerThread::readData(){
			mMutex.lock();
			std::vector<std::string> data = mData;
			mData.clear();
			mMutex.unlock();

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
			while(mIsRunning){
				char recvbuf[1024];
				int recvbuflen = 1024;

				int iResult = recv(mSocket, recvbuf, recvbuflen, 0);
				if (iResult > 0) {
					std::cout << "Connection " << mIndex << " has received " << iResult << "bytes" << std::endl;

					std::string msg;

					msg.append(recvbuf, iResult);
					std::vector<std::string> a;
					
					mMutex.lock();
					mData.push_back(msg);
					mMutex.unlock();
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