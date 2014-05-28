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
		template<int type_>
		int Socket<type_>::sendData(std::string _str) {
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
		template<int type_>
		std::string Socket<type_>::receiveData() {
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
		template<int type_>
		int Socket<type_>::getLastError(){
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
		template<int type_>
		ClientSocket<type_>* Socket<type_>::createClientSocket(std::string _ip, std::string _port){
			return new ClientSocket<type_>(_ip, _port);
		}
		//-----------------------------------------------------------------------------
		template<int type_>
		ServerSocket<type_>* Socket<type_>::createServerSocket(std::string _port){
			return new ServerSocket<type_>(_port);
		
		}
		//-----------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL
