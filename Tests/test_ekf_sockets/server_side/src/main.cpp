/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramon Soria
//		Date:	2014-03-12
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "core/comm/ServerMultiThread.h"

#include <vector>
#include <map>
#include <iostream>
#include <string>

std::map<std::string, std::string> parseArgs(int _argc, char** _argv);

int main(int _argc, char** _argv){
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);

	BOViL::comm::ServerMultiThread server(hashMap["PORT"]);

	std::vector<std::string> data;
	while (1){
		for (int i = 0; i < server.getNoConnections(); i++){
			if (server.getThread(i)->hasData()){
				data = server.getThread(i)->readData();
				for (unsigned int j = 0; j < data.size(); j++){
					std::cout << data[j] << std::endl;
				}
			}
		}
	}

	system("PAUSE");

	return 0;

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