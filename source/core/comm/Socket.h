/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-27
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_CORE_COMM_SOCKET_H_
#define _BOVIL_CORE_COMM_SOCKET_H_

#if defined(_WIN32)
	#include <WinSock2.h>
#endif

#include <string>

namespace BOViL{
	namespace comm{
		//-----------------------------------------------------------------------------
		class foo{
		public:
			foo(){
				struct addrinfo *result = nullptr,
								*ptr	= nullptr,
								hints;

				ZeroMemory(&hints, sizeof(hints));

				hints.ai_family = AF_UNSPEC;
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_protocol = IPPROTO_TCP;

				const std::string DEFAULT_PORT = "27015";

				int result = getaddrinfo("192.168.1.1", DEFAULT_PORT.c_str(), &hints, &result);
			}
		};
		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------

		//-----------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_CORE_COMM_SOCKET_H_