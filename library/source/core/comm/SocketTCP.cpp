/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-05-31
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "SocketTCP.h"

namespace BOVil{
	namespace comm{
		//-----------------------------------------------------------------------------
		bool SocketTCP::sendMsg(std::string _str) {
			if (send(mSocket, _str.c_str(), _str.size(), 0) == SOCKET_ERROR) {
				std::cout << "Socket Error" << std::endl;
				closeSocket();
				#if defined (_WIN32)
					std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
					WSACleanup();
				#endif
				return false;
			}

			return true;
		}

		//-----------------------------------------------------------------------------
		bool SocketTCP::receiveMsg(std::string &_msg) {
			char recvbuf[1024];
			int recvbuflen = 1024;

			int iResult = recv(mSocket, recvbuf, recvbuflen, 0);
			if (iResult < 0) {
				return false;
			}

			_msg.append(recvbuf, iResult);

			return true;
		}
	}
}




