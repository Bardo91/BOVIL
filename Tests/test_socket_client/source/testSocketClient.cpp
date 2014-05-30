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

using namespace BOViL::comm;

int testSocketClient(std::string _ip, std::string _port){
	ClientSocket<eSocketType::eTCP>* client = Socket::createClientSocket<eSocketType::eTCP>(_ip, _port);
	
	std::string msg = "Hello world";
	
	do {
		std::cin >> msg;
		std::cout << "Send: " << msg << std::endl;
		client->sendData(msg);
	} while(std::strcmp(msg.c_str(), "QUIT"));
	
	
	delete client;

	return 0;
}