/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-03-30
//		Last Update:	2014-05-31
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "Socket.h"

namespace BOViL	{
	namespace comm{
		//-----------------------------------------------------------------------------
		bool Socket::closeSocket(){
			return !closesocket(mSocket);

		}

		//-----------------------------------------------------------------------------
		int Socket::getLastError(){
			#if defined (_WIN32)
				int error = WSAGetLastError();
				WSACleanup();
				return error;
			#endif

			#if defined (__linux__)
				return errno;
			#endif
		}
	}	//	namespace comm
}	//	namespace BOViL
