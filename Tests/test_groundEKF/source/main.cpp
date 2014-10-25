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
		ss << "image";
		ss << _i;
		ss << ".jpg";

		return ss.str();
	};

	auto parser = [](double * _arr)->QuadState{
		QuadState state;

		state.eulerAngles[0]	= _arr[4];
		state.eulerAngles[1]	= _arr[5];
		state.eulerAngles[2]	= _arr[6];
		state.position[0]		= _arr[1];
		state.position[1]		= _arr[2];
		state.position[2]		= _arr[3];

		return state;
	};

	testSegmentation(hashMap["IMG_PATH"], nameGen, parser);

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
