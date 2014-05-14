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
#include <algorithms/state_estimators/GroundTrackingEKF.h>

// Includes of ppal libraries
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <fstream>

// Other includes

// CONSTS
const int PROGRAM_ID = 34;

const double PERSPECTIVE_ANGLE = 45;
const double CAM_WIDTH_PIX = 256;
const double FOCAL_LENGHT =  1 / (2 * tan(PERSPECTIVE_ANGLE / 2) / CAM_WIDTH_PIX);
const double U0 = 0;
const double V0 = 0;

const double arrayQ[16] = { 0.005, 0, 0, 0,
							0, 0.005, 0, 0,
							0, 0, 0.005, 0,
							0, 0, 0, 0.005 };

const double arrayR[4] = {	0.001, 0,
							0, 0.001 };

const double arrayX0[4] = { 0.0,//0, 
							0.0,//0, 
							0.0,//0, 
							0.0 };//0);

//---------------------------------------------------------------------------------------
//------------------------------- Other defs --------------------------------------------
//---------------------------------------------------------------------------------------

struct QuadFrameInFo{
	int mQuadId = -1;
	std::vector<BOViL::Point2d> mObjectsCentroid;	// 666 TODO: dont dont dont like it... but... size? u.u
	BOViL::math::Matrix<double> mPos = BOViL::math::Matrix<double>(3, 1);
	BOViL::math::Matrix<double> mOri = BOViL::math::Matrix<double>(3, 3);
	double mFrameTime = -1;
	bool updated = false;
};

//---------------------------------------------------------------------------------------
//-------------------------- Declaration of Functions -----------------------------------
//---------------------------------------------------------------------------------------
std::map<std::string, std::string> parseArgs(int _argc, char** _argv);
void watchThreadFn(std::string _port, QuadFrameInFo &_quadsFrameInfo);
void trackingThreadFn(QuadFrameInFo &_quadsFrameInfo);

void clearConsole();

//---------------------------------------------------------------------------------------
//------------------------------------- main --------------------------------------------
//---------------------------------------------------------------------------------------
int main(int _argc, char** _argv){
	// Decode input arguments
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);	
	
	// Start thread to watch connections
	QuadFrameInFo quadFrameInfo;
	std::thread watchThread(watchThreadFn, hashMap["PORT"], std::ref(quadFrameInfo));

	// Tracking
	std::thread trackingThread(trackingThreadFn, std::ref(quadFrameInfo));


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
				   quadFrameInfo.mObjectsCentroid.push_back(
					   BOViL::Point2d(	double(atof(substr.substr(0, substr.find("*")).c_str())),
										double(atof(substr.substr(substr.find("*") + 1, substr.length() - substr.find("*")).c_str()))));
			break;
		}
		}

		dataType++;
	}

	quadFrameInfo.updated = true;

	return quadFrameInfo;
}

//---------------------------------------------------------------------------------------
void watchThreadFn(std::string _port, QuadFrameInFo &_quadsFrameInfo){
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
					inLog << poolMessages[i] << std::endl;

					QuadFrameInFo quadFrameInfo =  decodeMessage(poolMessages[i]);

					mutex.lock();
					_quadsFrameInfo = quadFrameInfo;
					mutex.unlock();
				}

			}
		}
	}
}

//---------------------------------------------------------------------------------------
void trackingThreadFn( QuadFrameInFo &_quadFrameInfo){
	std::ofstream outLog("./out_log.txt");
	if (!outLog.is_open())
		assert(false);	// 666 TODO: do better
	
	std::mutex mutex;
	QuadFrameInFo quadFrameInfo;

	BOViL::math::Matrix<double> Q(arrayQ, 4, 4);
	BOViL::math::Matrix<double> R(arrayR, 2, 2);
	BOViL::math::Matrix<double> x0(arrayX0, 4, 1);
	
	BOViL::algorithms::GroundTrackingEKF ekf;

	ekf.setUpEKF(Q, R, x0);
	ekf.setUpCamera(FOCAL_LENGHT, U0, V0);
	
	double lastTime = 0.0;
	while (1){
		
		if (!_quadFrameInfo.updated)
			continue;

		mutex.lock();
		_quadFrameInfo.updated = false;
		quadFrameInfo = _quadFrameInfo;
		mutex.unlock();
				
		double arrayZk[2] = { double(quadFrameInfo.mObjectsCentroid[0].x), double(quadFrameInfo.mObjectsCentroid[0].y) };

		BOViL::math::Matrix<double> Zk(arrayZk, 2, 1);
		
		ekf.updateCamera(quadFrameInfo.mPos, quadFrameInfo.mOri, 0.0);
		ekf.stepEKF(Zk, quadFrameInfo.mFrameTime - lastTime);

		lastTime = quadFrameInfo.mFrameTime;

		BOViL::math::Matrix<double> stateVector = ekf.getStateVector();

		outLog << stateVector(0, 0) << ", " << stateVector(1, 0) << std::endl; 
		stateVector.showMatrix();
		
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