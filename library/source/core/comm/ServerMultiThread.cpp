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
			mServerSocket = ServerSocket(_PORT);

			mServerSocket.listenClient();

		}

		//-----------------------------------------------------------------------------
		ServerMultiThread::~ServerMultiThread(){


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