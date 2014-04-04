/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-28
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "core/comm/ServerSocket.h"
#include "testSocketsServer.h"

#include <iostream>

int testSocketsServer(std::string _port){
	BOViL::comm::ServerSocket* server = BOViL::comm::Socket::createServerSocket(_port);
	
	int iResult = 0;
	
	iResult += server->listenClient();
	iResult += server->acceptClient();
	
	if(iResult)
		return 1;
	
	std::string msg = "";
	
	do{
		msg = server->receiveData();
		std::cout << "Received: " << msg << std::endl;
	}while(std::strcmp(msg.c_str(), "QUIT"));

	return 0;
}