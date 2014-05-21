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
#include <fstream>

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

struct QuadFrameInFo{
	int mQuadId = -1;
	std::vector<BOViL::Point2d> mObjectsCentroid;	// 666 TODO: dont dont dont like it... but... size? u.u
	double mPos[3];
	double mOri[3];
	double mFrameIncTime = -1;
	bool newPoints = true;
	bool sended = true;
};

//---------------------------------------------------------------------------------------
//-------------------------- Declaration of Functions -----------------------------------
//---------------------------------------------------------------------------------------
std::map<std::string, std::string> parseArgs(int _argc, char** _argv);
void acquisitionThreadFn(cv::Mat &_bufferImage, std::string &_imgPath, std::string &_dataPath, QuadFrameInFo &_quadFrameInfo);
void segmentationThreadFn(cv::Mat &_image, QuadFrameInFo &_quadFrameInfo);
void communicationThreadFn(std::string _ip, std::string _port, QuadFrameInFo &_quadFrameInfo);

void visualizationThreadFn(cv::Mat &_image, bool &_visualize);

//---------------------------------------------------------------------------------------
//------------------------------------- main --------------------------------------------
//---------------------------------------------------------------------------------------
int main(int _argc, char** _argv){
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);

	std::string imagePath = hashMap["IMG_PATH"];
	std::string dataPath = hashMap["DATA_PATH"];

	QuadFrameInFo quadFrameInfo;
	quadFrameInfo.mQuadId = atoi(hashMap["QUAD_ID"].c_str());	// 777: In this test can only be 1 or 2

	running = true;

	// Get Camera information from the arguments
	CameraInfo camInfo(	BOViL::Point2i(atoi(hashMap["WIDTH"].c_str()), atoi(hashMap["HEIGHT"].c_str())),
						atof(hashMap["FL"].c_str()),
						BOViL::Point2d(
								double(atof(hashMap["U0"].c_str())), 
								double(atof(hashMap["V0"].c_str()))));

	// OpenCV image in the main thread
	cv::Mat bufferImage;
	std::vector<BOViL::ImageObject> objects;

	// Start threads
	std::thread imageAcquisitionThread(acquisitionThreadFn, std::ref(bufferImage), std::ref(imagePath), std::ref(dataPath), std::ref(quadFrameInfo));
	std::thread segmentationThread(segmentationThreadFn, std::ref(bufferImage), std::ref(quadFrameInfo));
	std::thread communicationThread(communicationThreadFn, hashMap["IP"], hashMap["PORT"], std::ref(quadFrameInfo));
	
	bool visualize = false;
	std::thread visualizationThread(visualizationThreadFn, std::ref(bufferImage), std::ref(visualize));

	std::mutex mutex;

	int command;
	do{
		std::cout << "\t QUAD ROTOR MAIN PROGRAM" << std::endl;
		std::cout << "\t \t Press 0 to stop the execution" << std::endl;
		std::cout << "\t \t Press 1 to enable/disable visualization" << std::endl;
		std::cout << "\t \t Press 2 to request fps" << std::endl;

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
bool openInputFile(std::ifstream& _inFile, std::string _path){
	_inFile.open(_path);

	if (!_inFile.is_open() || !_inFile.good())
		return false;

	return true;
}

//---------------------------------------------------------------------------------------
bool dropLineIntoBuffer(std::ifstream& _inFile, double* _buffer){
	std::string line;
	int colCounter = 0;
	int init = 0;
	int counter = 0;

	getline(_inFile, line);
	colCounter = line.size();

	if (colCounter < 0)
		return false;

	int index = 0;
	for (int i = 0; i < colCounter; i++) {
		if (((int)line.at(i)) == 9) {
			std::string part = line.substr(init, i - init);
			_buffer[index] = atof(part.c_str());
			init = i + 1;
			counter++;
			index++;
		}
	}

	return true;
}


//---------------------------------------------------------------------------------------
void acquisitionThreadFn(cv::Mat &_bufferImage, std::string &_imgPath, std::string &_dataPath, QuadFrameInFo &_quadFrameInfo){
	//	This functions is responsible for the image acquisition and the time span
	std::mutex mutex;

	std::ifstream inputFile;
	double inputBuffer[20];
	double lastTime = 0;

	cv::Mat inputImage;
	
	int imgIndex = 0;

	int quadID = _quadFrameInfo.mQuadId;
	mutex.lock();
	running  = openInputFile(inputFile, _dataPath);
	mutex.unlock();

	while (running){		// 666 TODO: whats about global variable or someway to control the exeution
		
		if (!_quadFrameInfo.newPoints)
			continue;

		std::stringstream ss;
		ss << _imgPath << "img" << imgIndex << "_cam" << quadID << ".jpg";

		inputImage = cv::imread(ss.str());

		mutex.lock();
		inputImage.copyTo(_bufferImage);
		mutex.unlock();
		
		dropLineIntoBuffer(inputFile, inputBuffer);		// Get objects info.
		
		// Pass object info.
		mutex.lock();
		_quadFrameInfo.mPos[0] = inputBuffer[(_quadFrameInfo.mQuadId - 1) * 6 + 7];
		_quadFrameInfo.mPos[1] = inputBuffer[(_quadFrameInfo.mQuadId - 1) * 6 + 8];
		_quadFrameInfo.mPos[2] = inputBuffer[(_quadFrameInfo.mQuadId - 1) * 6 + 9];
		
		_quadFrameInfo.mOri[0] = inputBuffer[(_quadFrameInfo.mQuadId - 1) * 6 + 10];
		_quadFrameInfo.mOri[1] = inputBuffer[(_quadFrameInfo.mQuadId - 1) * 6 + 11];
		_quadFrameInfo.mOri[2] = inputBuffer[(_quadFrameInfo.mQuadId - 1) * 6 + 12]; 
		_quadFrameInfo.mFrameIncTime = inputBuffer[0] - lastTime;
		mutex.unlock();

		mutex.lock();
		_quadFrameInfo.newPoints = false;
		mutex.unlock();

		lastTime = inputBuffer[0];
		
		//std::cout << lastTime << std::endl;

		imgIndex++;

		cv::waitKey(1);
	}

	std::cout << "Closing acquisition Thread" << std::endl;

}

//---------------------------------------------------------------------------------------
void segmentationThreadFn(cv::Mat &_image, QuadFrameInFo &_quadFrameInfo){
	// This function is responsible for the image segmentation
	cv::waitKey(100);

	std::mutex mutex;
	cv::Mat image;

	std::string windowsName = "Testing";		// 666 TODO: erase

	while (running) {		// 666 TODO: whats about global variable or someway to control the exeution
		if (!_quadFrameInfo.sended)
			continue;

		if (_quadFrameInfo.newPoints)
			continue;

		mutex.lock();
		_image.copyTo(image);
		_quadFrameInfo.newPoints = true;
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
			_quadFrameInfo.mObjectsCentroid.resize(objects.size());
			for (unsigned int i = 0; i < objects.size(); i++){
				_quadFrameInfo.mObjectsCentroid[i] =  BOViL::Point2d(objects[i].getCentroid().x, objects[i].getCentroid().y);
			}
			mutex.unlock();

			for (unsigned int i = 0; i < objects.size(); i++){
				mutex.lock();
				circle(	_image, 
						cv::Point(objects[i].getCentroid().x, objects[i].getCentroid().y), 
						objects[i].getHeight() / 2, 
						cv::Scalar(255, 255, 255));
				mutex.unlock();
			}

			mutex.lock();
			_quadFrameInfo.sended = false;
			mutex.lock();

		}


		cv::waitKey(1);
	}

	std::cout << "Closing segmentation Thread" << std::endl;

}

//---------------------------------------------------------------------------------------
void communicationThreadFn(std::string _ip, std::string _port, QuadFrameInFo &_quadFrameInfo){
	std::mutex mutex;

	// OUTPUTLOG
	std::ofstream outLog("./comm_log.txt");
	if (!outLog.is_open())
		assert(false);	// 666 TODO: do better

	std::vector<BOViL::Point2d> centroids;

	BOViL::comm::ClientSocket client(_ip, _port);

	while (running){
		if (_quadFrameInfo.sended)
			continue;

		mutex.lock();
		centroids = _quadFrameInfo.mObjectsCentroid;
		mutex.unlock();

		std::stringstream ssMsg;	// Msg protocol {PROJECT;ID;msg1-msg2-...-msgN;PROJECT}

		// 666 TODO: y el tiempo?
		if (centroids.size() == 0)
			continue;

		ssMsg << "{34;01;" << _quadFrameInfo.mFrameIncTime << ";0*0";

		for (unsigned int i = 0; i < centroids.size(); i++){
			ssMsg << "," << centroids[i].x << "*" << centroids[i].y ;
		}

		ssMsg << ";00}" << std::endl;
		
		int msgSize = ssMsg.str().length();

		client.sendData(ssMsg.str());

		mutex.lock();
		_quadFrameInfo.sended = true;
		mutex.unlock();

		outLog << ssMsg.str();

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