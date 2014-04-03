/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-29
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "core/comm/ClientSocket.h"
#include "testSocketClient.h"

#include <iostream>

int testSocketClient(std::string _ip, std::string _port){
	BOViL::comm::ClientSocket* client = BOViL::comm::Socket::createClientSocket(_ip, _port);
	
	std::string msg = "Hello world";
	
	do {
		std::cin >> msg;
		std::cout << "Send: " << msg << std::endl;
		client->sendData(msg);
	} while(std::strcmp(msg.c_str(), "QUIT"));
	
	
	delete client;

	return 0;
}