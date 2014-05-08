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
#include <core/time/time.h>

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

// 666 :::: GLOBAL for execution :::: MALA COSA... Pero es un test u.u
bool runningCondition, visualization;

//---------------------------------------------------------------------------------------
//-------------------------- Declaration of Functions -----------------------------------
//---------------------------------------------------------------------------------------
struct AcquisitionStatistics{
	int mNoImages = 0;
	double mLastFps = 0.0;
};
//---------------------------------------------------------------------------------------
//-------------------------- Declaration of Functions -----------------------------------
//---------------------------------------------------------------------------------------
std::map<std::string, std::string> parseArgs(int _argc, char** _argv);
void acquisitionThreadFn(AcquisitionStatistics &_statistics);

//---------------------------------------------------------------------------------------
//------------------------------------- main --------------------------------------------
//---------------------------------------------------------------------------------------
int main(int _argc, char** _argv){
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);
	
	std::mutex mutex;

	runningCondition = true;
	visualization = false;
	AcquisitionStatistics statistics;

	// Start threads
	std::thread imageAcquisitionThread(acquisitionThreadFn, std::ref(statistics));

	int command;
	do{
		std::cout << std::endl << "TEST IMAGE ACQUISITION AND STORAGE" << std::endl;
		std::cout << "\t Press 0 to stop the execution" << std::endl;
		std::cout << "\t Press 1 to see the number of acquisitions" << std::endl;
		std::cout << "\t Press 2 to see statistics" << std::endl;
		std::cout << "\t Press 3 to enable/disable visualization" << std::endl << std::endl;
		std::cout << std::endl;

		std::cin >> command;

		if (command == 0)
			continue;
		else if (command == 1){
			mutex.lock();
			int noImages = statistics.mNoImages;
			mutex.unlock();
			std::cout << "--> Number of images acquired since execution: " << noImages << std::endl;
		}
		else if (command == 2){
			mutex.lock();
			int fps = statistics.mLastFps;
			mutex.unlock();
			std::cout << "--> Last FPS was: " << fps << std::endl;
		}
		else if (command == 3){
			mutex.lock();
			visualization = !visualization;
			mutex.unlock();
		}

		
		std::cout.clear();


	} while (command != 0);

	// Stop thread
	runningCondition = false;
	cv::waitKey(100);

	if (imageAcquisitionThread.joinable()){
		imageAcquisitionThread.join();
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
void acquisitionThreadFn(AcquisitionStatistics &_statistics){
	//	This functions is responsible for the image acquisition and the time span
	BOViL::STime::init();
	BOViL::STime *sTime = BOViL::STime::get();
	
	std::mutex mutex;

	cv::Mat inputImage;
	cv::VideoCapture camera(0);
	
	if (!camera.isOpened())	// 666 TODO: forma mejor de parar la ejecución
		assert(false);

	std::string winName = "Visualization Test";

	while (runningCondition){		// 666 TODO: whats about global variable or someway to control the exeution
		double time = sTime->getTime();

		camera >> inputImage;

		time = sTime->getTime() - time;
		double fps = 1 / time;

		mutex.lock();
		_statistics.mNoImages++;
		_statistics.mLastFps = fps;
		mutex.unlock();

		if (visualization)
			cv::imshow(winName, inputImage);
		else
			cv::destroyWindow(winName);

		cv::waitKey(1);
	}

	BOViL::STime::end();
}