/////////////////////////////////////////////////////////////////////////////////////////
//	EC-SAFEMOBIL: Ground Station - Tracking Ground Objects
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-05
//
/////////////////////////////////////////////////////////////////////////////////////////

// Includes related to BOViL Libraries
#include <core/comm/ServerMultiThread.h>
#include <core/types/BasicTypes.h>

// Includes of ppal libraries
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <thread>

// Other includes


//---------------------------------------------------------------------------------------
//------------------------------- Other defs --------------------------------------------
//---------------------------------------------------------------------------------------

struct QuadFrameInFo{
	int quadId;
	std::vector<BOViL::Point2ui> objectsCentroid;	// 666 TODO: dont dont dont like it... but... size? u.u
	double frameTime;
};

//---------------------------------------------------------------------------------------
//-------------------------- Declaration of Functions -----------------------------------
//---------------------------------------------------------------------------------------
std::map<std::string, std::string> parseArgs(int _argc, char** _argv);
void watchThreadFn(BOViL::comm::ServerMultiThread &_server);
void trackingThreadFn();

//---------------------------------------------------------------------------------------
//------------------------------------- main --------------------------------------------
//---------------------------------------------------------------------------------------
int main(int _argc, char** _argv){
	// Decode input arguments
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);

	// Initiallize Server in the port received in input argument PORT.
	BOViL::comm::ServerMultiThread server(hashMap["PORT"]);

	// Start thread to watch connections
	std::thread watchThread(watchThreadFn, server);
	
	// Tracking
	std::thread trackingThread(trackingThreadFn);


	//	Interface With server
	int command;
	do{
		std::cout << "\t \t	\t GROUND STATION - SERVER INTERFACE  " << std::endl;
		std::cout << "\t --> Press 0 to close server" << std::endl;
		std::cout << "\t --> Press 1 to request ...." << std::endl;
		std::cout << "\t --> Press 2 to request ...." << std::endl;
	} while (command != 0);
	

	//	Detach Threads
	if (watchThread.joinable()){
		watchThread.detach();
	}
	if (trackingThread.joinable()){
		trackingThread.detach();
	}

	// END
	return 0;
}


//---------------------------------------------------------------------------------------
//--------------------------- Definition of Functions -----------------------------------
//---------------------------------------------------------------------------------------

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

//---------------------------------------------------------------------------------------
void watchThreadFn(BOViL::comm::ServerMultiThread &_server){


}

//---------------------------------------------------------------------------------------
void trackingThreadFn(){


}