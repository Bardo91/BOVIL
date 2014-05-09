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
#include <core/comm/ClientSocket.h>

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

// 666 GLOBAL VARIABLE---> DONT LIKE BUT ITS FASTER
bool running;

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

//---------------------------------------------------------------------------------------
//-------------------------- Declaration of Functions -----------------------------------
//---------------------------------------------------------------------------------------
std::map<std::string, std::string> parseArgs(int _argc, char** _argv);
void acquisitionThreadFn(cv::Mat &_bufferImage);
void segmentationThreadFn(cv::Mat &_image, std::vector<BOViL::ImageObject> &_objects);
void communicationThreadFn(std::vector<BOViL::ImageObject> &_objects, std::string _ip, std::string _port);

void visualizationThreadFn(cv::Mat &_image, bool &_visualize);

//---------------------------------------------------------------------------------------
//------------------------------------- main --------------------------------------------
//---------------------------------------------------------------------------------------
int main(int _argc, char** _argv){
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);

	running = true;

	// Get Camera information from the arguments
	CameraInfo camInfo(	BOViL::Point2i(atoi(hashMap["WIDTH"].c_str()), atoi(hashMap["HEIGHT"].c_str())),
						atof(hashMap["FL"].c_str()),
						BOViL::Point2d(atof(hashMap["U0"].c_str()), atof(hashMap["V0"].c_str())));

	// OpenCV image in the main thread
	cv::Mat bufferImage;
	std::vector<BOViL::ImageObject> objects;

	// Start threads
	std::thread imageAcquisitionThread(acquisitionThreadFn, std::ref(bufferImage));
	std::thread segmentationThread(segmentationThreadFn, std::ref(bufferImage), std::ref(objects));
	std::thread communicationThread(communicationThreadFn, std::ref(objects), hashMap["IP"], hashMap["PORT"]);
	
	bool visualize = false;
	std::thread visualizationThread(visualizationThreadFn, std::ref(bufferImage), std::ref(visualize));

	std::mutex mutex;

	int command;
	do{
		std::cout << "\t QUAD ROTOR MAIN PROGRAM" << std::endl;
		std::cout << "\t \t Press 0 to stop the execution" << std::endl;
		std::cout << "\t \t Press 1 to enable/disable visualization" << std::endl;
		std::cout << "\t \t Press 2 to enable/disable image storation" << std::endl;

		std::cin >> command;
		if (command == 0){
			mutex.lock();
			running = false;
			mutex.unlock();
			continue;
		}
		else if (command == 1){
			visualize = !visualize;
		}
		else if (command == 2){
			
		}

	} while (command != 0);

	// Stop threads
	if (imageAcquisitionThread.joinable()){
		imageAcquisitionThread.join();
	}if (segmentationThread.joinable()){
		segmentationThread.join();
	}if (communicationThread.joinable()){
		communicationThread.join();
	}if (visualizationThread.joinable()){
		visualizationThread.join();
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

	while (running){		// 666 TODO: whats about global variable or someway to control the exeution
		
		camera >> inputImage;

		mutex.lock();
		inputImage.copyTo(_bufferImage);
		mutex.unlock();

		//std::cout << "Cojo imagen \n";

		cv::waitKey(1);
	}

	std::cout << "Closing acquisition Thread" << std::endl;

}

//---------------------------------------------------------------------------------------
void segmentationThreadFn(cv::Mat &_image, std::vector<BOViL::ImageObject> &_objects){
	// This function is responsible for the image segmentation
	cv::waitKey(100);

	std::mutex mutex;
	cv::Mat image;

	std::string windowsName = "Testing";		// 666 TODO: erase

	while (running) {		// 666 TODO: whats about global variable or someway to control the exeution
		mutex.lock();
		_image.copyTo(image);
		mutex.unlock();

		//std::cout << "Segmento imagen \n";


		if (image.rows > 0){

			cv::medianBlur(image, image, 5);

			std::vector<BOViL::ImageObject> objects;
			BOViL::ColorClusterSpace *cs = BOViL::CreateHSVCS_8c(255U, 255U, std::uint8_t(BOViL::bin2dec("00010000")));

			cv::cvtColor(image, image, CV_BGR2HSV);

			BOViL::algorithms::ColorClustering<std::uint8_t>(image.data,		// Image pointer
				image.cols,		// Width
				image.rows,		// Height
				10,				// Size Threshold
				objects,		// Output Objects
				*cs);			// Segmentation function 

			mutex.lock();
			_objects = objects;
			mutex.unlock();

			for (int i = 0; i < objects.size(); i++){
				mutex.lock();
				circle(	_image, 
						cv::Point(objects[i].getCentroid().x, objects[i].getCentroid().y), 
						objects[i].getHeight() / 2, 
						cv::Scalar(255, 255, 255));
				mutex.unlock();
			}

		}

		cv::waitKey(1);
	}

	std::cout << "Closing segmentation Thread" << std::endl;

}

//---------------------------------------------------------------------------------------
void communicationThreadFn(std::vector<BOViL::ImageObject> &_objects, std::string _ip, std::string _port){
	std::mutex mutex;

	std::vector<BOViL::ImageObject> objects;

	BOViL::comm::ClientSocket client(_ip, _port);

	while (running){
		mutex.lock();
		objects= _objects;
		mutex.unlock();

		std::stringstream ssMsg;	// Msg protocol {PROJECT;ID;msg1-msg2-...-msgN;PROJECT}

		ssMsg << "{00;01";

		for (unsigned int i = 0; i < objects.size(); i++){
			ssMsg << objects[i].getCentroid().x << "," << objects[i].getCentroid().y << "-";
		}

		ssMsg << ";00}" << std::endl;
		
		int msgSize = ssMsg.str().length();

		client.sendData(ssMsg.str());

		//std::cout << objects.size()<< std::endl;
	}

	std::cout << "Closing communication Thread" << std::endl;

}

//---------------------------------------------------------------------------------------
void visualizationThreadFn(cv::Mat &_image, bool &_visualize){
	std::mutex mutex;
	cv::Mat image;
	
	while (running){	// 666 TODO
		if (_visualize){
			mutex.lock();
			_image.copyTo(image);
			mutex.unlock();

			if (image.rows != 0)
				cv::imshow("Visualization", image);

			cv::waitKey(1);

		} else{
			cv::destroyAllWindows();
			cv::waitKey(100);
		}
	}

	std::cout << "Closing visualization Thread" << std::endl;

}