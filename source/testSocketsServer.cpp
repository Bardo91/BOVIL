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

	int iResult = 0;

	iResult += static_cast<BOViL::comm::ServerSocket*>(server)->listenClient();
	iResult += static_cast<BOViL::comm::ServerSocket*>(server)->acceptClient();

	if(iResult)
		return 1;

	std::string msg = "";

	do{
		msg = server->receiveData();
		std::cout << "Received: " << msg << std::endl;
	}while(!msg.compare("ERROR"));

	return 0;
}