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

		}

		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
		void ServerMultiThread::acceptFunction(){
			while(1){
				SOCKET conn = mServerSocket.acceptClient();
				if(conn != 0){
					mThreadList[mNoConnections] = AuxiliarServerThread(conn, mNoConnections);
					mNoConnections++;
				}
			}
		}
		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
	}	//	 namespace BOViL
}	//	namespace comm