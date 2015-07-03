/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-28
//
/////////////////////////////////////////////////////////////////////////////////////////

#include <core/comm/ServerSocketTCP.h>
#include "testSocketsServer.h"

#include <iostream>

using namespace BOViL::comm;

int testSocketsServer(std::string _port){
	Socket *socket = Socket::createSocket(eSocketType::serverTCP, "2048");
	
	std::string msg = "";
	
	do{
		msg.clear();
		socket->receiveMsg(msg);
		std::cout << "Received: " << msg << std::endl;
	}while(std::strcmp(msg.c_str(), "QUIT"));

	delete socket;

	return 0;
}