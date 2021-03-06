/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-05-12
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "TestSegmentation.h"

#include <core/math/geometrics/Geometrics.h>

static const double arrayQ[36] = {	0.05, 0, 0, 0, 0, 0, 
									0, 0.05, 0, 0, 0, 0, 
									0, 0, 0.05, 0, 0, 0, 
									0, 0, 0, 0.05, 0, 0, 
									0, 0, 0, 0, 0.05, 0, 
									0, 0, 0, 0, 0, 0.05};

static const double arrayR[16] = {	0.1, 0, 0, 0, 
									0, 0.1, 0, 0, 
									0, 0, 0.1, 0, 
									0, 0, 0, 0.1};

static const double arrayX0[6] = {	8.0,//0, 
									12.0,//0, 
									0,//0, 
									0,//0, 
									0,//0, 
									0};//0);


using namespace BOViL::math;

bool openInputFile(std::ifstream& _inFile, std::string _path);
bool dropLineIntoBuffer(std::ifstream& _inFile, double* _buffer);

void testSegmentation(){
	///////////////////////////////////////////////////
	std::ofstream outFile;
	std::string pathName;
	pathName = "./outputFile_StereoTracking.txt";
	outFile.open(pathName.c_str());
	///////////////////////////////////////////////////


	std::cout << "TESTING SEGMENTATION ALGORITHM && EKF" << std::endl;
	cv::Mat img1, ori1, img2, ori2;

	std::string path = "";

	#if defined (__linux)
		path = "/home/bardo91/Programming/Images/";
	#endif
	#if defined (_WIN32)
		path = "C:/Programming/ImagenesStereoTracking/P2_640x480/Images/";	
	#endif
	
	std::cout << "--Path of images: " << path << std::endl;

	bool condition = true;
	int i = 0;

	std::cout << "--Init Timer" << std::endl;
	BOViL::STime::init();

	BOViL::STime *time = BOViL::STime::get();

	double t0, t1;

	std::cout << "--Create Clustered Space" << std::endl;
	BOViL::ColorClusterSpace *cs = BOViL::CreateHSVCS_8c(255U,255U, std::uint8_t(BOViL::bin2dec("00010000")));

	//-------
	std::cout << "--Init Stereo EKF" << std::endl;
	BOViL::algorithms::StereoVisionEKF stereoEKF;

	stereoEKF.setUpEKF(	Matrix<double>(arrayQ, 6, 6),
						Matrix<double>(arrayR, 4, 4),
						Matrix<double>(arrayX0, 6, 1));

	stereoEKF.setUpCameras(738.143358488352310, 346.966835812843040 , 240.286986071815390);
	double inputBuffer[20];
	std::ifstream inputFile;
	
	std::cout << "--Open Input File" << std::endl;
	
	#if defined (__linux)
		condition = openInputFile(inputFile, "/home/bardo91/Programming/Images/ViconData2.txt");
	#endif
	#if defined (_WIN32)
		condition = openInputFile(inputFile, "C:/Programming/ImagenesStereoTracking/P2_640x480/ViconData2.txt");	
	#endif

	double lastTime = 0;


	while(condition){

		//t0 = time->getTime();

		// ----------------- IMAGE SEGMENTATION ------------------------
		std::stringstream ss1, ss2;

		ss1 << path;
		ss1 << "img";
		ss1 << i;
		ss2 << ss1.str();
		ss1 << "_cam1.jpg";
		ss2 << "_cam2.jpg";

		std::string imagePath1 = ss1.str();
		std::string imagePath2= ss2.str();
		
		img1 = cv::imread(imagePath1, CV_LOAD_IMAGE_COLOR);
		img2 = cv::imread(imagePath2, CV_LOAD_IMAGE_COLOR);

		img1.copyTo(ori1);
		img2.copyTo(ori2);

		t0 = time->getTime();
		std::vector<BOViL::ImageObject> objects1;
		std::vector<BOViL::ImageObject> objects2;

		cv::cvtColor(img1, img1, CV_BGR2HSV);
		cv::cvtColor(img2, img2, CV_BGR2HSV);

		BOViL::algorithms::ColorClustering<std::uint8_t>(	img1.data,		// Image pointer
															img1.cols,		// Width
															img1.rows,		// Height
															5,				// Size Threshold
															objects1,		// Output Objects
															*cs);			// Segmentation function 
														
		BOViL::algorithms::ColorClustering<std::uint8_t>(	img2.data,		// Image pointer
															img2.cols,		// Width
															img2.rows,		// Height
															5,				// Size Threshold
															objects2,		// Output Objects
															*cs);			// Segmentation function 


		
		t1 = time->getTime();
		double fps = 1/(t1-t0);
		std::cout << fps << " fps" << std::endl;
		std::cout << "Number of detected Objects1 in the scene: " << objects1.size() << std::endl;
		std::cout << "Number of detected Objects2 in the scene: " << objects2.size() << std::endl;

		int maxY1 = 0, maxIndex1 = 0;
		int maxY2 = 0, maxIndex2 = 0;

		if (objects1.size() != 0 && objects2.size() != 0){
			// Select Object
			
			for (unsigned int obj = 0; obj < objects1.size(); obj++){
				if (objects1[obj].getCentroid().y > maxY1){
					maxY1 = objects1[obj].getCentroid().y;
					maxIndex1 = obj;
				}
			}
			
			for (unsigned int obj = 0; obj < objects2.size(); obj++){
				if (objects2[obj].getCentroid().y > maxY2){
					maxY2 = objects2[obj].getCentroid().y;
					maxIndex2 = obj;
				}
			}

			BOViL::Point2ui p = objects1[maxIndex1].getCentroid();
			cv::circle(ori1, cv::Point2d(p.x, p.y), objects1[maxIndex1].getHeight() / 2, cv::Scalar(0, 255, 0), 1);

			p = objects2[maxIndex2].getCentroid();
			cv::circle(ori2, cv::Point2d(p.x, p.y), objects2[maxIndex2].getHeight() / 2, cv::Scalar(0, 255, 0), 1);
		}

		cv::hconcat(ori1, ori2, ori1);
		cv::imshow("ORIGINAL", ori1);


		// ----------------- TRACKING ALGORITHM ------------------------
		dropLineIntoBuffer(inputFile, inputBuffer);		// Get objects info.

		if (objects1.size() == 0 || objects2.size() == 0)
			continue;


		// Update cameras pos and ori
		double arrayPosC1[3] = {inputBuffer[7], inputBuffer[8], inputBuffer[9]};
		double arrayPosC2[3] = {inputBuffer[13], inputBuffer[14], inputBuffer[15]};


		Matrix<double> Rx = createRotationMatrix(eEdges::EdgeX, inputBuffer[10]);
		Matrix<double> Ry = createRotationMatrix(eEdges::EdgeY, inputBuffer[11]);
		Matrix<double> Rz = createRotationMatrix(eEdges::EdgeZ, inputBuffer[12]);

		Matrix<double> camOri1 = Rz*Ry*Rx;

		Rx = createRotationMatrix(eEdges::EdgeX, inputBuffer[16]);
		Ry = createRotationMatrix(eEdges::EdgeY, inputBuffer[17]);
		Rz = createRotationMatrix(eEdges::EdgeZ, inputBuffer[18]);

		Matrix<double> camOri2 = Rz*Ry*Rx;

		Matrix<double> adaptRot =	createRotationMatrix(eEdges::EdgeX, PiCte / 2) *
									createRotationMatrix(eEdges::EdgeZ, PiCte / 2);


		stereoEKF.updateCameras(Matrix<double>(arrayPosC1, 3, 1),
								Matrix<double>(arrayPosC2, 3, 1),	
								adaptRot*camOri1,
								adaptRot*camOri2);

		double arrayZk[4] = {	double (objects1[maxIndex1].getCentroid().x),
								img1.rows - double (objects1[maxIndex1].getCentroid().y),
								double (objects2[maxIndex2].getCentroid().x),
								img2.rows - double(objects2[maxIndex2].getCentroid().y) };

		stereoEKF.stepEKF(Matrix<double>(arrayZk, 4, 1), inputBuffer[0] - lastTime);
		lastTime = inputBuffer[0];

		Matrix<double> state =  stereoEKF.getStateVector();

		state.showMatrix();
		
		outFile << inputBuffer[0] << "\t" << state[0] << "\t" << state[1] << "\t" << state[2] << "\t" << arrayZk[0] << "\t" << arrayZk[1] << "\t" << arrayZk[2] << "\t" << arrayZk[3] << "\n";

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
