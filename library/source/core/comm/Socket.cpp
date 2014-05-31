/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//			Author:		Pablo Ramon Soria
//			Date:		2014-03-30
//		Last Update:	2014-05-31
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "Socket.h"

#include "ServerSocketTCP.h"
#include "ClientSocketTCP.h"

#include <cassert>

namespace BOViL	{
	namespace comm{
		//-----------------------------------------------------------------------------
		// Socket Factory
		Socket* Socket::createSocket(const eSocketType _socketType, const std::string &_serverPort, const std::string &_serverIp){
			switch (_socketType)
			{
			case eSocketType::serverTCP:
				return new ServerSocketTCP(_serverPort);
				break;
			case eSocketType::clientTCP:
				return new ClientSocketTCP(_serverIp, _serverPort);
				break;
			case eSocketType::serverUDP:
				return nullptr;
				break;
			case eSocketType::clientUDP:
				return nullptr;
				break;
			default:
				return nullptr;
			}
		}

		//-----------------------------------------------------------------------------
		Socket::Socket(): mSocket(INVALID_SOCKET) {
			#if defined (_WIN32) 
				// Initialize Winsock
				if (WSAStartup(MAKEWORD(2, 2), &mWsaData) != 0) {
					assert(false);
				}
			#endif
		}
		
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
