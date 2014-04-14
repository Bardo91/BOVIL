
/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramon Soria
//		Date:	2014-04-08
//
/////////////////////////////////////////////////////////////////////////////////////////

#include <core/time/time.h>

#include <vector>
#include <map>
#include <iostream>
#include <string>

std::map<std::string, std::string> parseArgs(int _argc, char** _argv);

int main(int _argc, char** _argv){
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);

	BOViL::STime::init();

	BOViL::STime *time = BOViL::STime::get();

	while (1){
		std::cout << time->frameTime() << std::endl;
	}

	#if defined(_WIN32)
		system("PAUSE");
	#endif
	
	//delete client;	//	 666 TODO: add destructor.

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
