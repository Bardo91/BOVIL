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
		template<int type_>
		ServerMultiThread<type_>::ServerMultiThread(std::string _PORT) :	mNoConnections(0) {
			mServerSocket = ServerSocket(_PORT);
			
			mServerSocket.listenClient();

			mAcceptThread = std::thread(&ServerMultiThread::acceptFunction, this);

		}

		//-----------------------------------------------------------------------------
		template<int type_>
		ServerMultiThread<type_>::~ServerMultiThread(){
			if(mAcceptThread.joinable())
				mAcceptThread.join();
			
			for(int i = 0; i < mNoConnections ; i++){
				delete mThreadList[i];
			}
		}

		//-----------------------------------------------------------------------------
		template<int type_>
		int ServerMultiThread<type_>::getNoConnections(){
			return mNoConnections;

		}

		//-----------------------------------------------------------------------------
		template<int type_>
		AuxiliarServerThread* ServerMultiThread<type_>::getThread(int _index){
			return mThreadList[_index];

		}

		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
		template<int type_>
		void ServerMultiThread<type_>::acceptFunction(){
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