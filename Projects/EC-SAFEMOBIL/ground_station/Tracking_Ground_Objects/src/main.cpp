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
#include <core/math/Matrix.h>
#include <core/math/geometrics/Geometrics.h>

// Includes of ppal libraries
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <fstream>

// Other includes


const int PROGRAM_ID = 34;

//---------------------------------------------------------------------------------------
//------------------------------- Other defs --------------------------------------------
//---------------------------------------------------------------------------------------

struct QuadFrameInFo{
	int mQuadId = -1;
	std::vector<BOViL::Point2ui> mObjectsCentroid;	// 666 TODO: dont dont dont like it... but... size? u.u
	BOViL::math::Matrix<double> mPos = BOViL::math::Matrix<double>(3, 1);
	BOViL::math::Matrix<double> mOri = BOViL::math::Matrix<double>(3, 3);
	double mFrameTime = -1;
};

//---------------------------------------------------------------------------------------
//-------------------------- Declaration of Functions -----------------------------------
//---------------------------------------------------------------------------------------
std::map<std::string, std::string> parseArgs(int _argc, char** _argv);
void watchThreadFn(std::string _port, std::vector<QuadFrameInFo> &_quadsFrameInfo);
void trackingThreadFn(std::vector<std::vector<std::string>> &_messages);

void clearConsole();

//---------------------------------------------------------------------------------------
//------------------------------------- main --------------------------------------------
//---------------------------------------------------------------------------------------
int main(int _argc, char** _argv){
	// Decode input arguments
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);

	// Message Container
	std::vector<std::vector<std::string>> messages;
	
	// Start thread to watch connections
	std::vector<QuadFrameInFo> quadsFrameInfo;
	std::thread watchThread(watchThreadFn, hashMap["PORT"], std::ref(quadsFrameInfo));

	// Tracking
	std::thread trackingThread(trackingThreadFn, std::ref(messages));


	//	Interface With server
	std::mutex mutex;

	int command;
	do{
		std::cout <<  std::endl;
		std::cout << "GROUND STATION - SERVER INTERFACE  " << std::endl;
		std::cout << "\t --> Press 0 to close server" << std::endl;
		std::cout << "\t --> Press 1 to request statistics" << std::endl;
		std::cout << "\t --> Press 2 to request ...." << std::endl;

		std::cin >> command;

		switch (command)
		{
		case 1:{		// Request statistics
			   clearConsole();
			   mutex.lock();
			   int frameTime = 0;


			   std::cout << "" << std::endl;
		}
		case 2:
			clearConsole();

			std::cout << "" << std::endl;
		}

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
QuadFrameInFo decodeMessage(std::string _message){
	QuadFrameInFo quadFrameInfo;

	int pos = 0, lastPos = 0;
	int dataType = 0;	// dataType 0 = program ; 1 = quad ID ; 4 = frameTime ;3 = quad position ; 4 = quad orientation; 5 = centroids
	while ((pos = _message.find(";", pos + 1)) != std::string::npos){

		std::string substr = _message.substr(lastPos, pos - lastPos);

		lastPos = pos + 1;

		switch (dataType)
		{
		case 0:{
			int programId = atoi(substr.c_str());
			if (programId != PROGRAM_ID)
				assert(false);
			
			break;
		}	
		case 1:{
			quadFrameInfo.mQuadId = atoi(substr.c_str());
			break;
		}
		case 2:{
			quadFrameInfo.mFrameTime = atof(substr.c_str());
			break;
		}
		case 3:{
			quadFrameInfo.mPos(0, 0) = double(atof(substr.substr(0, substr.find(",")).c_str()));
			quadFrameInfo.mPos(1, 0) = double(atof(substr.substr(substr.find(",") + 1, substr.find_last_of(",") - substr.find(",") - 1).c_str()));
			quadFrameInfo.mPos(2, 0) = double(atof(substr.substr(substr.find_last_of(",") + 1, substr.length()).c_str()));

			break;
		}
		case 4:{
				   quadFrameInfo.mOri = BOViL::math::createRotationMatrixEuler(
					   double(atof(substr.substr(0, substr.find(",")).c_str())),
					   double(atof(substr.substr(substr.find(",") + 1, substr.find_last_of(",") - substr.find(",") - 1).c_str())),
					   double(atof(substr.substr(substr.find_last_of(",") + 1, substr.length()).c_str())));
			break;
		}
		case 5:{
			break;
		}
		}

		dataType++;
	}

	return quadFrameInfo;
}

//---------------------------------------------------------------------------------------
void watchThreadFn(std::string _port, std::vector<QuadFrameInFo> &_quadsFrameInfo){
	std::mutex mutex;

	BOViL::comm::ServerMultiThread server(_port);

	// inputlog
	std::ofstream inLog("./in_log.txt");
	if (!inLog.is_open())
		assert(false);	// 666 TODO: do better

	while (1){
		// Check number of connections
		int noCon = server.getNoConnections();

		// Read information
		for (int i = 0; i < noCon; i++){
			BOViL::comm::AuxiliarServerThread *conn = server.getThread(i);
			if (conn != nullptr && conn->hasData()){
				std::vector<std::string> poolMessages = conn->readData();
				for (unsigned int i = 0; i < poolMessages.size(); i++){
					inLog << poolMessages[i];

					QuadFrameInFo quadFrameInfo =  decodeMessage(poolMessages[i]);

					mutex.lock();
					_quadsFrameInfo.push_back(quadFrameInfo);
					mutex.unlock();
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

//---------------------------------------------------------------------------------------
void clearConsole(){
#if defined (_WIN32)
	system("cls");
#elif defined (__linux__)
	system("clear");
#endif

}