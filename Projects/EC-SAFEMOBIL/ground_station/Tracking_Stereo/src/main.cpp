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
#include <algorithms/state_estimators/StereoVisionEKF.h>

#include "MathGeometrics.h"


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
const double U0 = 256 / 2;
const double V0 = 256 / 2;

const double arrayQ[36] = { 0.05, 0, 0, 0, 0, 0,
							0, 0.05, 0, 0, 0, 0,
							0, 0, 0.05, 0, 0, 0, 
							0, 0, 0, 0.05, 0, 0,
							0, 0, 0, 0, 0.05, 0,
							0, 0, 0, 0, 0, 0.05};

const double arrayR[16] = {	0.1, 0, 0, 0,
							0, 0.1, 0, 0,
							0, 0, 0.1, 0,
							0, 0, 0, 0.1};

const double arrayX0[6] = { 0.0,//0, 
							0.0,//0, 
							0.0,//0, 
							0.0,
							0.0,
							0.0};//0);

//---------------------------------------------------------------------------------------
//------------------------------- Other defs --------------------------------------------
//---------------------------------------------------------------------------------------

struct QuadFrameInFo{
	int mQuadId = -1;
	std::vector<BOViL::Point2d> mObjectsCentroid;	// 666 TODO: dont dont dont like it... but... size? u.u
	BOViL::math::Matrix<double> mPos = BOViL::math::Matrix<double>(3, 1);
	BOViL::math::Matrix<double> mOri = BOViL::math::Matrix<double>(3, 3);
	double mFrameIncTime = -1;
	bool updated = false;
};

//---------------------------------------------------------------------------------------
//-------------------------- Declaration of Functions -----------------------------------
//---------------------------------------------------------------------------------------
std::map<std::string, std::string> parseArgs(int _argc, char** _argv);
void watchThreadFn(std::string _port, QuadFrameInFo &_quadFrameInfo1, QuadFrameInFo &_quadFrameInfo2);
void trackingThreadFn(QuadFrameInFo &_quadFrameInfo1, QuadFrameInFo &_quadFrameInfo2);

void clearConsole();

//---------------------------------------------------------------------------------------
//------------------------------------- main --------------------------------------------
//---------------------------------------------------------------------------------------
int main(int _argc, char** _argv){
	// Decode input arguments
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);	
	
	// Start thread to watch connections
	QuadFrameInFo quadFrameInfo1, quadFrameInfo2;
	std::thread watchThread(watchThreadFn, hashMap["PORT"], std::ref(quadFrameInfo1), std::ref(quadFrameInfo2));

	// Tracking
	std::thread trackingThread(trackingThreadFn, std::ref(quadFrameInfo1), std::ref(quadFrameInfo2));


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
			   int fps1 = 1 / quadFrameInfo1.mFrameIncTime;
			   int fps2 = 1 / quadFrameInfo2.mFrameIncTime;
			   mutex.unlock();

			   std::cout << "--> Quadrotor 1 runs algorithm with fps = " << fps1 << std::endl;
			   std::cout << "--> Quadrotor 2 runs algorithm with fps = " << fps2 << std::endl;

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
			quadFrameInfo.mFrameIncTime = atof(substr.c_str());
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
void watchThreadFn(std::string _port, QuadFrameInFo &_quadFrameInfo1, QuadFrameInFo &_quadFrameInfo2){
	std::mutex mutex;

	BOViL::comm::ServerMultiThread server(_port);

	// inputlog
	std::ofstream inLog1("./in_log_quad1.txt");
	std::ofstream inLog2("./in_log_quad2.txt");
	if (!inLog1.is_open() || !inLog2.is_open())
		assert(false);	// 666 TODO: do better

	while (1){
		// Check number of connections
		int noCon = server.getNoConnections();

		// Read information
		for (int i = 0; i < noCon; i++){
			BOViL::comm::AuxiliarServerThread *conn = server.getThread(i);
			if (conn != nullptr && conn->hasData()){
				
				
				

				//----------------------------------------------------------------------------------------------
				// Read all messages
				//----------------------------------------------------------------------------------------------
				std::vector<std::string> poolMessages = conn->readData();
				std::vector<QuadFrameInFo> poolQuadFrameInfo;
				for (unsigned int i = 0; i < poolMessages.size(); i++){
					poolQuadFrameInfo.push_back(decodeMessage(poolMessages[i]));
				}


				//----------------------------------------------------------------------------------------------
				// Lets try a modification, only read last info received
				//----------------------------------------------------------------------------------------------
				//std::vector<std::string> poolMessages = conn->readData();
				//
				//QuadFrameInFo quadFrameInfo = decodeMessage(poolMessages[poolMessages.size() - 1]);
				//
				//if (quadFrameInfo.mQuadId == 1)
				//	inLog1 << poolMessages[poolMessages.size() - 1] << std::endl;
				//else if (quadFrameInfo.mQuadId == 2)
				//	inLog2 << poolMessages[poolMessages.size() - 1] << std::endl;
				//
				//
				//if (quadFrameInfo.mQuadId == 1){
				//	mutex.lock();
				//	_quadFrameInfo1 = quadFrameInfo;
				//	mutex.unlock();
				//}
				//else if (quadFrameInfo.mQuadId == 2){
				//	mutex.lock();
				//	_quadFrameInfo2 = quadFrameInfo;
				//	mutex.unlock();
				//}
			}
		}
	}
}

//---------------------------------------------------------------------------------------
void trackingThreadFn(QuadFrameInFo &_quadFrameInfo1, QuadFrameInFo &_quadFrameInfo2){
	std::ofstream outLog("./out_log.txt");
	if (!outLog.is_open())
		assert(false);	// 666 TODO: do better
	
	std::mutex mutex;
	QuadFrameInFo quadFrameInfo1, quadFrameInfo2;

	BOViL::math::Matrix<double> Q(arrayQ, 6, 6);
	BOViL::math::Matrix<double> R(arrayR, 4, 4);
	BOViL::math::Matrix<double> x0(arrayX0, 6, 1);
	
	BOViL::algorithms::StereoVisionEKF ekf;

	ekf.setUpEKF(Q, R, x0);
	ekf.setUpCameras(FOCAL_LENGHT, U0, V0);
	
	double lastTime = 0.0;
	while (1){
		
		if (!_quadFrameInfo1.updated || !_quadFrameInfo2.updated)
			continue;
		
		mutex.lock();
		_quadFrameInfo1.updated = false;
		_quadFrameInfo2.updated = false;
		quadFrameInfo1 = _quadFrameInfo1;
		quadFrameInfo2 = _quadFrameInfo2;
		mutex.unlock();
			
		// 666 TODO: Where is the matching???? now take first element of the list
		double arrayZk[4] = {	double(quadFrameInfo1.mObjectsCentroid[0].x),
								double(quadFrameInfo1.mObjectsCentroid[0].y), 
								double(quadFrameInfo2.mObjectsCentroid[0].x),
								double(quadFrameInfo2.mObjectsCentroid[0].y) };
		
		BOViL::math::Matrix<double> Zk(arrayZk, 4, 1);
		
		ekf.updateCameras(quadFrameInfo1.mPos, quadFrameInfo2.mPos, quadFrameInfo1.mOri, quadFrameInfo2.mOri);
		
		// 666 TODO: asegurarse que se envia el incremento de tiempo, no el tiempo en si.
		double medTime = (quadFrameInfo1.mFrameIncTime + quadFrameInfo2.mFrameIncTime) / 2;
		ekf.stepEKF(Zk, medTime - lastTime);	// 666 TODO Probar cual es el mejor tiempo???

		
		lastTime = medTime;
		
		BOViL::math::Matrix<double> stateVector = ekf.getStateVector();
		
		outLog << stateVector(0, 0) << "\t" << stateVector(1, 0) << "\t" << stateVector(2, 0) << std::endl;
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