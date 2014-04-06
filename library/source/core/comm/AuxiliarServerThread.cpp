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
		AuxiliarServerThread::AuxiliarServerThread(){

		}

		//-----------------------------------------------------------------------------
		AuxiliarServerThread::AuxiliarServerThread(SOCKET _socket, int _index){
			mSocket = _socket;
			mIndex = _index;
			mThread = nullptr;
			startThread();

		}
		//-----------------------------------------------------------------------------
		AuxiliarServerThread::~AuxiliarServerThread(){
			std::cout << "Closing connection: " << mIndex << std::endl;
			while(!stopThread());

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
			if(mThread !=nullptr && mThread->joinable()){
				mThread->join();
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
			return mData;
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
					printf("Bytes received: %d\n", iResult);

					std::string msg;

					msg.append(recvbuf, iResult);
					std::vector<std::string> a;
					
					mData.push_back(msg);

				}
			}
		}

		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL