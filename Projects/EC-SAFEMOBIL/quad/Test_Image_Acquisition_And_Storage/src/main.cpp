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
void acquisitionThreadFn(AcquisitionStatistics &_statistics, std::string &_imgPath);

//---------------------------------------------------------------------------------------
//------------------------------------- main --------------------------------------------
//---------------------------------------------------------------------------------------
int main(int _argc, char** _argv){
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);
	
	std::mutex mutex;

	std::string imagePath;
	if (hashMap.count("IMG_PATH"))
		imagePath = hashMap["IMG_PATH"];
	else
		imagePath = "images";

	runningCondition = true;
	visualization = false;
	AcquisitionStatistics statistics;

	// Start threads
	std::thread imageAcquisitionThread(acquisitionThreadFn, std::ref(statistics), std::ref(imagePath));
	
	int command;
	do{
		std::cout << std::endl << std::endl << "TEST IMAGE ACQUISITION AND STORAGE" << std::endl;
		std::cout << "\t --> Standar image output path: " << imagePath << std::endl;
		std::cout << "\t Press 0 to stop the execution" << std::endl;
		std::cout << "\t Press 1 to see the number of acquisitions" << std::endl;
		std::cout << "\t Press 2 to see statistics" << std::endl;
		std::cout << "\t Press 3 to enable/disable visualization" << std::endl;
		std::cout << "\t Press 4 to change image path. Example 'C:/Images' or '/home/user/Images'. DONT ADD '/' at the end!! " << std::endl << std::endl;
		std::cout << std::endl;

		std::cin >> command;

		#ifdef _WIN32
				system("cls");
		#endif
		#ifdef  __linux__
				system("clear");
		#endif

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
		else if (command == 4){
			std::cout << "--> Introduce path: ";
			std::cin >> imagePath;

		}

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
void acquisitionThreadFn(AcquisitionStatistics &_statistics, std::string &_imgPath){
	//	This functions is responsible for the image acquisition and the time span
	// Init timer
	BOViL::STime::init();
	BOViL::STime *sTime = BOViL::STime::get();
	
	// Create mutex for safe multithread operations
	std::mutex mutex;
	
	//Gget image Folder path
	mutex.lock();
	std::string imagePath = _imgPath;
	mutex.unlock();
	std::string imgName = "/image";
	
	// Create folder if not created
	std::stringstream ssFolderCommand;
	ssFolderCommand << "mkdir " << _imgPath;
	system("@echo off");
	system(ssFolderCommand.str().c_str());

	// Init camera
	cv::Mat inputImage;
	cv::VideoCapture camera(0);
	
	if (!camera.isOpened())	// 666 TODO: forma mejor de parar la ejecución
		assert(false);

	// Window name
	std::string winName = "Visualization Test";
	
	// Main Thread loop
	while (runningCondition){		// 666 TODO: whats about global variable or someway to control the exeution
		
		mutex.lock();
		if (imagePath.length() != _imgPath.length()){
			
			imagePath = _imgPath;
			mutex.unlock();

			// Update folder path
			ssFolderCommand.str("");
			ssFolderCommand << "mkdir " << _imgPath;
			system("@echo off");
			system(ssFolderCommand.str().c_str());
		}
		else
			mutex.unlock();

		


		double time = sTime->getTime();

		camera >> inputImage;

		std::stringstream ss;
		ss << imagePath << imgName;
		
		mutex.lock();
		int number = _statistics.mNoImages;
		mutex.unlock();
		
		ss << number << ".jpg";

		std::string imageName = ss.str();

		cv::imwrite(imageName, inputImage);

		/*if (inputImage.rows != 0){
			std::thread storeThread([imageName, inputImage]() {
				cv::imwrite(imageName, inputImage);
			});
			storeThread.join();
		}*/

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