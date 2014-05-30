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

using namespace BOViL::comm;

int testSocketsServer(std::string _port){
	ServerSocket<eSocketType::eTCP>* server = Socket::createServerSocket<eSocketType::eTCP>(_port);
	
	int socket = 0;
	
	server->listenClient();
	socket = server->acceptClient();
	
	if(!socket)
		return 1;
	
	std::string msg = "";
	
	do{
		msg = server->receiveData();
		std::cout << "Received: " << msg << std::endl;
	}while(std::strcmp(msg.c_str(), "QUIT"));

	return 0;
}