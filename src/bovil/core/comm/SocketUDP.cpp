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
		int SocketUDP::sendMsg(const unsigned char *_buffer, const unsigned _bufferSize) {
			if (sendto(mSocket, (char*)_buffer, _bufferSize, 0, (sockaddr *) &mAddr, sizeof(mAddr)) == SOCKET_ERROR) {
				std::cout << "Socket Error" << std::endl;
				closeSocket();
				#if defined (_WIN32)
					//std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
					WSACleanup();
				#endif
				return -1;
			}

			return 0;
		}

		//-----------------------------------------------------------------------------
		int SocketUDP::receiveMsg(unsigned char *_buffer, const unsigned _bufferSize) {		
			#if defined(_WIN32)
				return recvfrom(mSocket, (char*) _buffer, _bufferSize, 0, mHints.ai_addr, (int*)mHints.ai_addrlen);
			#elif defined(__linux__)
				return recvfrom(mSocket, (void *)_buffer, _bufferSize, 0, mHints.ai_addr, &mHints.ai_addrlen);
			#endif
		}
	}
}

