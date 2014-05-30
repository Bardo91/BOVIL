//////////////////////////////////////////////////////////////////////////////////////////
//																						//
//		Test UDP socket																	//
//			Date:	2014-05-29															//
//			Author:	Pablo Ramon Soria													//
//																						//
//////////////////////////////////////////////////////////////////////////////////////////

#include <core/comm/ClientSocket.h>
#include <map>
#include <string>

using namespace BOViL::comm;
using namespace std;

std::map<std::string, std::string> parseArgs(int _argc, char** _argv);

int main(int _argc, char** _argv){
	map<string, string> hashMap = parseArgs(_argc, _argv);

	ClientSocket<eSocketType::eUDP>* clientSocket = Socket::createClientSocket<eSocketType::eUDP>(hashMap["IP"], hashMap["PORT"]);

	bool condition = true;

	string msg;

	while (condition){
		cin >> msg;

		if (msg.compare("QUIT"))
			condition = false;
		else
			clientSocket->sendData(msg);
	}
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
