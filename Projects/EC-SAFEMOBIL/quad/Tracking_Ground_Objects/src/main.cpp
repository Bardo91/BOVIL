/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: quad Tracking Ground Objects
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-05
//
/////////////////////////////////////////////////////////////////////////////////////////


// Includes related to BOViL Libraries
#include <core/types/BasicTypes.h>

// Includes of ppal libraries
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <thread>

// Other includes

//---------------------------------------------------------------------------------------
//-------------------------- Declaration of Functions -----------------------------------
//---------------------------------------------------------------------------------------
struct CameraInfo{
public:
	CameraInfo(BOViL::Point2ui _resolution, float _focalLenght, BOViL::Point2d _centroid){
		mResolution = _resolution;
		mFocalLenght = _focalLenght;
		mCentroid = _centroid;
	}
public:
	BOViL::Point2ui mResolution;
	float mFocalLenght;
	BOViL::Point2d mCentroid; 
};

struct FrameInfo {


};

//---------------------------------------------------------------------------------------
//-------------------------- Declaration of Functions -----------------------------------
//---------------------------------------------------------------------------------------
std::map<std::string, std::string> parseArgs(int _argc, char** _argv);
void acquisitionThreadFn();
void segmentationThreadFn();

//---------------------------------------------------------------------------------------
//------------------------------------- main --------------------------------------------
//---------------------------------------------------------------------------------------
int main(int _argc, char** _argv){
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);


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
void acquisitionThreadFn(){
	//	This functions is responsible for the image acquisition and the time span
}

//---------------------------------------------------------------------------------------
void segmentationThreadFn(){

}

//---------------------------------------------------------------------------------------