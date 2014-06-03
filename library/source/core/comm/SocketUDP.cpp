/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-05-31
//
/////////////////////////////////////////////////////////////////////////////////////////


#include "SocketUDP.h"

namespace BOViL{
	namespace comm{
		//-----------------------------------------------------------------------------
		bool SocketUDP::sendMsg(std::string _str) {
			if (sendto(mSocket, _str.c_str(), _str.size(), 0, (sockaddr *) &mAddr, sizeof(mAddr)) == SOCKET_ERROR) {
				std::cout << "Socket Error" << std::endl;
				closeSocket();
				#if defined (_WIN32)
					//std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
					WSACleanup();
				#endif
				return false;
			}

			return true;
		}

		//-----------------------------------------------------------------------------
		bool SocketUDP::receiveMsg(std::string &_msg) {
			char recvbuf[1024];
			int recvbuflen = 1024;
			int iResult;			
			#if defined(_WIN32)
				iResult = recvfrom(mSocket, recvbuf, recvbuflen, 0, mHints.ai_addr, (int*)mHints.ai_addrlen);
			#elif defined(__linux__)
				iResult = recvfrom(mSocket, recvbuf, recvbuflen, 0, mHints.ai_addr, mHints.ai_addrlen);
			#endif
			if (iResult < 0) {
				return false;
			}

			_msg.append(recvbuf, iResult);

			return true;
		}
	}
}

