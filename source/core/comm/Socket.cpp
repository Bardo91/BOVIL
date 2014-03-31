/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-30
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "Socket.h"
#if defined(_WIN32)
	#include "so_deps/win32/ClientSocketWin32.h"
	#include "so_deps/win32/ServerSocketWin32.h"
#endif
#if defined(__linux__)
	#include "so_deps/linux/ClientSocketLinux.h"
	#include "so_deps/linux/ServerSocketLinux.h"
#endif

namespace BOViL	{
	namespace comm{
		//-----------------------------------------------------------------------------
		Socket* Socket::createClientSocket(std::string _ip, std::string _port){
			return new ClientSocket(_ip, _port);
		}
		//-----------------------------------------------------------------------------
		Socket* Socket::createServerSocket(std::string _port){
			return new ServerSocket(_port);

		}
		//-----------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL