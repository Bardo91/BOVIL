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
	BOViL::comm::ClientSocket client;

	client.initializeSocket(_ip, _port);

	std::string msg = "Hello world";

	while(1){
		std::cout << "Send: " << msg << std::endl;
		client.sendStr(msg);
	}

}