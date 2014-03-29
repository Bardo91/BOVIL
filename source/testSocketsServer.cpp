/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-28
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "core/comm/ServerSocket.h"

#include <iostream>

int testSocketsServer(std::string _port){
	BOViL::comm::ServerSocket server;

	server.initializeSocket(_port);

	server.acceptClient();

	std::string msg = "";

	do{
		msg = server.receiveStr();
		std::cout << "Received: " << msg << std::endl;
	}while(!msg.compare("ERROR"));

	return 0;
}