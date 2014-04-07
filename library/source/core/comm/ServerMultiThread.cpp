/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-06
//
/////////////////////////////////////////////////////////////////////////////////////////


#include "ServerMultiThread.h"


namespace BOViL {
	namespace comm {
		//-----------------------------------------------------------------------------
		ServerMultiThread::ServerMultiThread(std::string _PORT) {
			mNoConnections = 0;
			mServerSocket = ServerSocket(_PORT);
			
			mServerSocket.listenClient();

			mAcceptThread = std::thread(&ServerMultiThread::acceptFunction, this);

		}

		//-----------------------------------------------------------------------------
		ServerMultiThread::~ServerMultiThread(){
			if(mAcceptThread.joinable())
				mAcceptThread.join();
			
			for(int i = 0; i < mNoConnections ; i++){
				delete mThreadList[i];
			}
		}

		//-----------------------------------------------------------------------------
		int ServerMultiThread::getNoConnections(){
			return mNoConnections;

		}

		//-----------------------------------------------------------------------------
		AuxiliarServerThread* ServerMultiThread::getThread(int _index){
			return mThreadList[_index];

		}

		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
		void ServerMultiThread::acceptFunction(){
			while(1){
				SOCKET conn = mServerSocket.acceptClient();
				if(conn != 0){
					mThreadList[mNoConnections] = new AuxiliarServerThread(conn, mNoConnections, mThreadList);
					mNoConnections++;
				}
			}
		}
		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
	}	//	 namespace BOViL
}	//	namespace comm