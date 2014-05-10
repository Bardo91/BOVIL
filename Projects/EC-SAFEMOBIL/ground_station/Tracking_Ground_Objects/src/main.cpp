/////////////////////////////////////////////////////////////////////////////////////////
//	EC-SAFEMOBIL: Ground Station - Tracking Ground Objects
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-05
//
/////////////////////////////////////////////////////////////////////////////////////////

// Includes related to BOViL Libraries
#include <core/comm/AuxiliarServerThread.h>
#include <core/comm/ServerMultiThread.h>
#include <core/types/BasicTypes.h>

// Includes of ppal libraries
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <fstream>

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
void watchThreadFn(BOViL::comm::ServerMultiThread &_server, std::vector<std::vector<std::string>> &_messages);
void trackingThreadFn(std::vector<std::vector<std::string>> &_messages);

//---------------------------------------------------------------------------------------
//------------------------------------- main --------------------------------------------
//---------------------------------------------------------------------------------------
int main(int _argc, char** _argv){
	// Decode input arguments
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);

	// Message Container
	std::vector<std::vector<std::string>> messages;

	// Initiallize Server in the port received in input argument PORT.
	BOViL::comm::ServerMultiThread server(hashMap["PORT"]);

	// Start thread to watch connections
	std::thread watchThread(watchThreadFn, std::ref(server), std::ref(messages));
	
	// Tracking
	std::thread trackingThread(trackingThreadFn, std::ref(messages));


	//	Interface With server
	int command;
	do{
		std::cout <<  std::endl;
		std::cout << "GROUND STATION - SERVER INTERFACE  " << std::endl;
		std::cout << "\t --> Press 0 to close server" << std::endl;
		std::cout << "\t --> Press 1 to request ...." << std::endl;
		std::cout << "\t --> Press 2 to request ...." << std::endl;

		std::cin >> command;
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
void watchThreadFn(BOViL::comm::ServerMultiThread &_server, std::vector<std::vector<std::string>> &_messages){
	std::mutex mutex;

	// inputlog
	std::ofstream inLog("./in_log.txt");
	if (!inLog.is_open())
		assert(false);	// 666 TODO: do better


	while (1){
		// Check number of connections
		int noCon = _server.getNoConnections();

		// Check if has list to every connection.
		mutex.lock();
		int sizeMsg = _messages.size();
		mutex.unlock();
		if (noCon < sizeMsg){
			_messages.resize(noCon);
		}

		// Read information
		std::vector<std::string> poolMessages;
		for (int i = 0; i < noCon; i++){
			BOViL::comm::AuxiliarServerThread *conn = _server.getThread(i);
			if (conn != nullptr && conn->hasData()){
				poolMessages = conn->readData();
				
				// 666 TODO: decode info etc...

				int quadId = atoi("0");
				//mutex.lock();
				//for (unsigned int i = 0; i < poolMessages.size(); i++){
				//	//_messages[quadId].push_back(poolMessages[i].substr(7,poolMessages[i].size()-4));
				//}
				//mutex.unlock();				

				for (unsigned int i = 0; i < poolMessages.size(); i++){
					inLog << poolMessages[i];
				}

			}
		}
	}
}

//---------------------------------------------------------------------------------------
void trackingThreadFn(std::vector<std::vector<std::string>> &_messages){
	while (1){

	}
}