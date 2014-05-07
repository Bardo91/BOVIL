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
#include <mutex>

// Other includes
#include <opencv/cv.h>
#include <opencv/highgui.h>

//---------------------------------------------------------------------------------------
//-------------------------- Declaration of Functions -----------------------------------
//---------------------------------------------------------------------------------------
struct CameraInfo{
public:
	CameraInfo(BOViL::Point2i _resolution, float _focalLenght, BOViL::Point2d _centroid){
		mResolution = _resolution;
		mFocalLenght = _focalLenght;
		mCentroid = _centroid;
	}
public:
	BOViL::Point2i mResolution;
	float mFocalLenght;
	BOViL::Point2d mCentroid; 
};

struct FrameInfo {


};

//---------------------------------------------------------------------------------------
//-------------------------- Declaration of Functions -----------------------------------
//---------------------------------------------------------------------------------------
std::map<std::string, std::string> parseArgs(int _argc, char** _argv);
void acquisitionThreadFn(cv::Mat &_bufferImage);
void segmentationThreadFn(cv::Mat &_image);
void communicationThreadFn();

//---------------------------------------------------------------------------------------
//------------------------------------- main --------------------------------------------
//---------------------------------------------------------------------------------------
int main(int _argc, char** _argv){
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);

	// Get Camera information from the arguments
	CameraInfo camInfo(	BOViL::Point2i(atoi(hashMap["WIDTH"].c_str()), atoi(hashMap["HEIGHT"].c_str())),
						atof(hashMap["FL"].c_str()),
						BOViL::Point2d(atof(hashMap["U0"].c_str()), atof(hashMap["V0"].c_str())));

	// OpenCV image in the main thread
	cv::Mat bufferImage;

	// Start threads
	std::thread imageAcquisitionThread(acquisitionThreadFn, std::ref(bufferImage));
	std::thread segmentationThread(segmentationThreadFn, std::ref(bufferImage));
	std::thread communicationThread(communicationThreadFn);

	while (true) {


	}

	// Stop threads
	if (imageAcquisitionThread.joinable()){
		imageAcquisitionThread.detach();
	}if (segmentationThread.joinable()){
		segmentationThread.detach();
	}if (communicationThread.joinable()){
		communicationThread.detach();
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

		cv::waitKey(1);
	}

}

//---------------------------------------------------------------------------------------
void segmentationThreadFn(cv::Mat &_image){
	// This function is responsible for the image segmentation
	cv::waitKey(100); //	Waiting the other thread to get one image.

	std::mutex mutex;
	cv::Mat image;

	std::string windowsName = "Testing";		// 666 TODO: erase

	while (true) {		// 666 TODO: whats about global variable or someway to control the exeution

		mutex.lock();
		_image.copyTo(image);
		mutex.unlock();

		if (image.rows > 0)
			cv::imshow(windowsName, image);

		cv::waitKey(1);
	}


}

//---------------------------------------------------------------------------------------
void communicationThreadFn(){


}