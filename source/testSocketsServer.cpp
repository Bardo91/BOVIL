/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-28
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "core/comm/Socket.h"
#include "core/comm/ServerSocket.h"
#include "testSocketsServer.h"
#include <iostream>

int testSocketsServer(std::string _port){
	BOViL::comm::Socket* server = BOViL::comm::Socket::createServerSocket(_port);

	static_cast<BOViL::comm::ServerSocket*>(server)->listenClient();
	static_cast<BOViL::comm::ServerSocket*>(server)->acceptClient();

	std::string msg = "";

	do{
		msg = server->receiveData();
		std::cout << "Received: " << msg << std::endl;
	}while(!msg.compare("ERROR"));

	return 0;
}