/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-05-12
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "TestGroundEKF.h"

#include <core/math/geometrics/Geometrics.h>

using namespace BOViL::math;

static const double arrayQ[16] = {	0.05, 0, 0, 0,
									0, 0.05, 0, 0,
									0, 0, 0.05, 0,
									0, 0, 0, 0.05 };

static const double arrayR[4] = {	0.1, 0, 
									0, 0.1 };

static const double arrayX0[4] = {	0.0,//0, 
									0.0,//0, 
									0.0,//0, 
									0.0};//0);


bool openInputFile(std::ifstream& _inFile, std::string _path);
bool dropLineIntoBuffer(std::ifstream& _inFile, double* _buffer);

void testSegmentation(){
	///////////////////////////////////////////////////
	std::ofstream outFile;
	std::string pathName;
	pathName = "./outputFile_GroundTracking.txt";
	outFile.open(pathName.c_str());
	///////////////////////////////////////////////////


	std::cout << "TESTING SEGMENTATION ALGORITHM && EKF" << std::endl;
	cv::Mat img, ori;

	std::string path = "";

	#if defined (__linux)
		path = "/home/bardo91/Programming/Images/";
	#endif
	#if defined (_WIN32)
		path = "C:/Programming/ImagenesStereoTracking/P1_640x480/Images/";	
	#endif
	
	std::cout << "--Path of images: " << path << std::endl;

	bool condition = true;
	int i = 0;

	std::cout << "--Init Timer" << std::endl;
	BOViL::STime::init();

	BOViL::STime *time = BOViL::STime::get();

	double t0, t1, t2, t3;

	std::cout << "--Create Clustered Space" << std::endl;
	BOViL::ColorClusterSpace *cs = BOViL::CreateHSVCS_8c(255U,255U, std::uint8_t(BOViL::bin2dec("00010000")));

	//-------
	std::cout << "--Init Stereo EKF" << std::endl;
	BOViL::algorithms::GroundTrackingEKF groundEKF;

	groundEKF.setUpEKF(Matrix<double>(arrayQ, 4, 4),
						Matrix<double>(arrayR, 2, 2),
						Matrix<double>(arrayX0, 4, 1));

	groundEKF.setUpCamera(738.143358488352310, 346.966835812843040, 240.286986071815390);
	double inputBuffer[20];
	std::ifstream inputFile;
	
	std::cout << "--Open Input File" << std::endl;
	
	#if defined (__linux)
		condition = openInputFile(inputFile, "/home/bardo91/Programming/Images/ViconData2.txt");
	#endif
	#if defined (_WIN32)
		condition = openInputFile(inputFile, "C:/Programming/ImagenesStereoTracking/P1_640x480/ViconData2.txt");	
	#endif

	double lastTime = 0;

	
	while(condition){
		t0 = time->getTime();

		// ----------------- IMAGE SEGMENTATION ------------------------
		std::stringstream ss;

		ss << path;
		ss << "img";
		ss << i;
		ss << "_cam1.jpg";

		std::string imagePath = ss.str();
		
		img = cv::imread(imagePath, CV_LOAD_IMAGE_COLOR);

		img.copyTo(ori);

		std::vector<BOViL::ImageObject> objects;

		cv::cvtColor(img, img, CV_BGR2HSV);

		BOViL::algorithms::ColorClustering<std::uint8_t>(	img.data,		// Image pointer
															img.cols,		// Width
															img.rows,		// Height
															5,				// Size Threshold
															objects,		// Output Objects
															*cs);			// Segmentation function 

		t1 = time->getTime();
		std::cout << "Number of detected Objects1 in the scene: " << objects.size() << std::endl;

		// ----------------- TRACKING ALGORITHM ------------------------
		
		// Select Oject
		int maxSize = 0, maxIndex = 0;
		for(unsigned int obj = 0; obj < objects.size() ; ++obj){
			if(objects[obj].getSize() > maxSize){
				maxSize = objects[obj].getSize();
				maxIndex = obj;
			}
		}

		BOViL::Point2ui p = objects[maxIndex].getCentroid();
		cv::circle(ori, cv::Point2d(p.x, p.y), objects[maxIndex].getHeight() / 2, cv::Scalar(0, 255, 0), 1);

		cv::imshow("ORIGINAL", ori);

		t2 = time->getTime();
		dropLineIntoBuffer(inputFile, inputBuffer);		// Get objects info.
		// Update cameras pos and ori
		
		Matrix<double> camOri = createRotationMatrix(eEdges::EdgeX, inputBuffer[10])*
			createRotationMatrix(eEdges::EdgeY, inputBuffer[11])*
			createRotationMatrix(eEdges::EdgeZ, inputBuffer[12]);
		

		Matrix<double> adaptRot =	createRotationMatrix(eEdges::EdgeX, PiCte / 2)*
									createRotationMatrix(eEdges::EdgeZ, PiCte);

		
		camOri = adaptRot*camOri;

		//Matrix<double> camOri = createRotationMatrixEuler(inputBuffer[10] - 3.1416 / 2, inputBuffer[11], inputBuffer[12] - 3.1416 / 2);

		double arrayPosC1[3] = { inputBuffer[7], inputBuffer[8], inputBuffer[9] };
		groundEKF.updateCamera(	BOViL::math::Matrix<double>(arrayPosC1, 3, 1), camOri, inputBuffer[3]);

		// EKF step
		double arrayZk[2] = {	double (objects[maxIndex].getCentroid().x),
								double (objects[maxIndex].getCentroid().y)};

		groundEKF.stepEKF(Matrix<double>(arrayZk, 2, 1), inputBuffer[0] - lastTime);
		lastTime = inputBuffer[0];

		Matrix<double> state = groundEKF.getStateVector();

		t3 = time->getTime();
		//double fps = 1 / (t1 - t0);
		//std::cout << fps << " fps" << std::endl;

		state.showMatrix();
		
		outFile << inputBuffer[0] << "\t" << state[0] << "\t" << state[1] << "\t" << state[2] << "\t" << arrayZk[0] << "\t" << arrayZk[1] << "\t" << 1 / (t1 - t0) << "\t" << 1 / (t3 - t2) << "\n";

		cv::waitKey(1);

		++i;
	}

	std::cout << "----------End----------" << std::endl;

}


bool openInputFile(std::ifstream& _inFile, std::string _path){
	_inFile.open(_path);

	if(!_inFile.is_open() || !_inFile.good())
			return false;

	return true;
}

bool dropLineIntoBuffer(std::ifstream& _inFile, double* _buffer){
	std::string line;
	int colCounter = 0;
	int init = 0;
	int counter = 0;

	getline(_inFile, line);
	colCounter = line.size();

	if(colCounter < 0)
		return false;
				
	int index = 0;
	for (int i = 0; i < colCounter; i++) {
		if (((int) line.at(i)) == 9) {
			std::string part = line.substr(init, i - init);
			_buffer[index] = atof(part.c_str());
			init = i + 1;
			counter++;
			index++;
		}
	}

	return true;
}
