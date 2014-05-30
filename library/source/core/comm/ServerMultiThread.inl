/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-06
//
/////////////////////////////////////////////////////////////////////////////////////////


namespace BOViL {
	namespace comm {
		//-----------------------------------------------------------------------------
		template<eSocketType type_>
		ServerMultiThread<type_>::ServerMultiThread(std::string _PORT) :	mNoConnections(0) {
			mServerSocket = ServerSocket(_PORT);
			
			mServerSocket.listenClient();

			mAcceptThread = std::thread(&ServerMultiThread::acceptFunction, this);

		}

		//-----------------------------------------------------------------------------
		template<eSocketType type_>
		ServerMultiThread<type_>::~ServerMultiThread(){
			if(mAcceptThread.joinable())
				mAcceptThread.join();
			
			for(int i = 0; i < mNoConnections ; i++){
				delete mThreadList[i];
			}
		}

		//-----------------------------------------------------------------------------
		template<eSocketType type_>
		int ServerMultiThread<type_>::getNoConnections(){
			return mNoConnections;

		}

		//-----------------------------------------------------------------------------
		template<eSocketType type_>
		AuxiliarServerThread* ServerMultiThread<type_>::getThread(int _index){
			return mThreadList[_index];

		}

		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
		template<eSocketType type_>
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