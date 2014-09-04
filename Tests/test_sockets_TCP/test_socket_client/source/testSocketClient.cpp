/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-29
//
/////////////////////////////////////////////////////////////////////////////////////////

#include <core/comm/Socket.h>
#include "testSocketClient.h"

#include <iostream>

using namespace BOViL::comm;

int testSocketClient(std::string _ip, std::string _port){
	Socket *socket = Socket::createSocket(eSocketType::clientTCP, _port, _ip);
	
	std::string msg = "Hello world";
	
	do {
		std::cin >> msg;
		std::cout << "Send: " << msg << std::endl;
		socket->sendMsg(msg);
	} while(std::strcmp(msg.c_str(), "QUIT"));
	
	
	delete socket;

	return 0;
}