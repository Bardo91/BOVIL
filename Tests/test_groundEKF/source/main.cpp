/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-03-12
//
/////////////////////////////////////////////////////////////////////////////////////////


#include "TestGroundEKF.h"

#include <vector>
#include <map>
#include <iostream>
#include <sstream>

using namespace std;

map<string, string> parseArgs(int _argc, char** _argv);

int main(int _argc, char** _argv){
	map<string, string> hashMap = parseArgs(_argc, _argv);

	auto nameGen = [](unsigned int _i)->string{
		stringstream ss;
		ss << "img";
		ss << _i;
		ss << "_cam1.jpg";

		return ss.str();
	};

	testSegmentation(hashMap["IMG_PATH"], nameGen);

	system("PAUSE");

	return 0;

}

std::map<std::string, std::string> parseArgs(int _argc, char** _argv){
	std::map<std::string, std::string> hashMap;
	for(int i = 1 ; i < _argc ; i++){
		std::string arg(_argv[i]);
		size_t next = arg.find_first_of('=');
		std::string type = arg.substr(0, next);
		arg = arg.substr(next + 1, arg.size());
		hashMap[type] = arg;
		std::cout << "Detected argument: " << type << " - With value: " << arg << std::endl;
	}
	return hashMap;
}
