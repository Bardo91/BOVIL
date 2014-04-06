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
		AuxiliarServerThread::AuxiliarServerThread(SOCKET _socket){
			mSocket = _socket;

			mThread = std::thread(&AuxiliarServerThread::watchFunction, this);

			mThread.detach();

			mIsRunning = true;
		}

		//-----------------------------------------------------------------------------
		int AuxiliarServerThread::startThread(){


		}

		//-----------------------------------------------------------------------------
		int AuxiliarServerThread::stopThread(){

		}

		//-----------------------------------------------------------------------------
		bool AuxiliarServerThread::hasData(){

		}

		//-----------------------------------------------------------------------------
		std::string AuxiliarServerThread::readData(){

		}

		//-----------------------------------------------------------------------------
		int AuxiliarServerThread::writeData(std::string _data){

		}

		//-----------------------------------------------------------------------------
		void AuxiliarServerThread::watchFunction(){

		}

		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL