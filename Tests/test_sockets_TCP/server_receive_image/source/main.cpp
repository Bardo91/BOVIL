///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		ImgReceiver
//			Author:	Pablo Ramon Soria
//			Date:	2014/09/04
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------------------------------------------------
#include <string>
#include <map>
#include <iostream>

#include "socket/socketMgr.h"

//---------------------------------------------------------------------------------------------------------------------
using namespace std;

//---------------------------------------------------------------------------------------------------------------------
map<string, string> parseArgs(int _argc, char** _argv);

const unsigned int PORT = 5028;

//---------------------------------------------------------------------------------------------------------------------
int main(int _argc, char** _argv){
	map<string, string> hashMap = parseArgs(_argc, _argv);

	SocketMgr socketMgr(PORT);
	volatile boolean condition = true;

	while (condition){

	}
}


//---------------------------------------------------------------------------------------------------------------------
map<string, string> parseArgs(int _argc, char** _argv){
	map<string, string> hashMap;
	for (int i = 1; i < _argc; i++){
		string arg(_argv[i]);
		size_t next = arg.find_first_of('=');
		string type = arg.substr(0, next);
		arg = arg.substr(next + 1, arg.size());
		hashMap[type] = arg;
		cout << "Detected argument: " << type << " - With value: " << arg << endl;
	}
	return hashMap;
}
