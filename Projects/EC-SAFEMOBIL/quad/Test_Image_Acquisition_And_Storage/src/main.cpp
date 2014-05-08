/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: quad Tracking Ground Objects
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-05
//
/////////////////////////////////////////////////////////////////////////////////////////


// Includes related to BOViL Libraries
#include <core/types/BasicTypes.h>
#include <algorithms/segmentation/ColorClustering.h>

// Includes of ppal libraries
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <mutex>
#include <cstdint>

// Other includes
#include <opencv/cv.h>
#include <opencv/highgui.h>

//---------------------------------------------------------------------------------------
//-------------------------- Declaration of Functions -----------------------------------
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//-------------------------- Declaration of Functions -----------------------------------
//---------------------------------------------------------------------------------------
std::map<std::string, std::string> parseArgs(int _argc, char** _argv);
void acquisitionThreadFn(cv::Mat &_bufferImage);

//---------------------------------------------------------------------------------------
//------------------------------------- main --------------------------------------------
//---------------------------------------------------------------------------------------
int main(int _argc, char** _argv){
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);

	// OpenCV image in the main thread
	cv::Mat bufferImage;

	// Start threads
	std::thread imageAcquisitionThread(acquisitionThreadFn, std::ref(bufferImage));

	int command;
	do{
		std::cout << "/t TEST IMAGE ACQUISITION AND STORAGE" << std::endl;
		std::cout << "/t /t Press 0 to stop the execution" << std::endl;
		std::cout << "/t /t Press 1 to see the number of acquisitions" << std::endl;
		std::cout << "/t /t Press 2 to see statistics" << std::endl;

		std::cin >> command;

	} while (command != 0);

	// Stop threads
	if (imageAcquisitionThread.joinable()){
		imageAcquisitionThread.detach();
	}
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
void acquisitionThreadFn(cv::Mat &_bufferImage){
	//	This functions is responsible for the image acquisition and the time span
	std::mutex mutex;

	cv::Mat inputImage;
	cv::VideoCapture camera(0);
	
	if (!camera.isOpened())	// 666 TODO: forma mejor de parar la ejecución
		assert(false);

	while (true){		// 666 TODO: whats about global variable or someway to control the exeution
		
		camera >> inputImage;

		mutex.lock();
		inputImage.copyTo(_bufferImage);
		mutex.unlock();

		std::cout << "Cojo imagen \n";

		cv::waitKey(1);
	}

}