/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-03-30
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "Sockets.h"

#include "ClientSocket.h"
#include "ServerSocket.h"

namespace BOViL	{
	namespace comm{
				//-----------------------------------------------------------------------------
		int Socket::sendData(std::string _str) {
			// Echo the buffer back to the sender
			int iSendResult = send( mSocketOut, _str.c_str(), _str.size(), 0 );
			if (iSendResult == SOCKET_ERROR) {
				std::cout << "Socket Error" << std::endl;
				closeSocket();
				#if defined (_WIN32)
					std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
					WSACleanup();
				#endif
				return 1;
			}
			//printf("Bytes sent: %d\n", iSendResult);
			
			return 0;
		}
		
		//-----------------------------------------------------------------------------
		std::string Socket::receiveData() {
			char recvbuf[1024];
			int recvbuflen = 1024;

			int iResult = recv(mSocketOut, recvbuf, recvbuflen, 0);
			if (iResult < 0) {
				return "ERROR";
			}
			//printf("Bytes received: %d\n", iResult);

			std::string msg;

			msg.append(recvbuf, iResult);

			return msg;
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

		//-----------------------------------------------------------------------------
		ClientSocket* Socket::createClientSocket(std::string _ip, std::string _port){
			return new ClientSocket(_ip, _port);
		}
		//-----------------------------------------------------------------------------
		ServerSocket* Socket::createServerSocket(std::string _port){
			return new ServerSocket(_port);
		
		}
		//-----------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL
