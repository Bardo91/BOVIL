//////////////////////////////////////////////////////////////////////////////////////////
//																						//
//		Test UDP socket																	//
//			Date:	2014-05-29															//
//			Author:	Pablo Ramon Soria													//
//																						//
//////////////////////////////////////////////////////////////////////////////////////////

#include <core/comm/Socket.h>

#include <map>
#include <string>

using namespace BOViL::comm;
using namespace std;

std::map<std::string, std::string> parseArgs(int _argc, char** _argv);

int main(int _argc, char** _argv){
	map<string, string> hashMap = parseArgs(_argc, _argv);

	Socket* client = Socket::createSocket(eSocketType::clientUDP, "2048", "");

	string msg;
	bool condition = true;

	do {
		std::cin >> msg;
		std::cout << "Send: " << msg << std::endl;
		condition = client->sendMsg(msg);
	} while (condition && std::strcmp(msg.c_str(), "QUIT"));
}

std::map<std::string, std::string> parseArgs(int _argc, char** _argv){
	std::map<std::string, std::string> hashMap;
	for (int i = 1; i < _argc; i++){
		std::string arg(_argv[i]);
		size_t next = arg.find_first_of('=');
		std::string type = arg.substr(0, next);
		arg = arg.substr(next + 1, arg.size());
		hashMap[type] = arg;
		std::cout << "Detected argument: " << type << " - With value: " << arg << std::endl;
	}
	return hashMap;
}
