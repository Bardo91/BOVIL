/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-12
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "TestSegmentation.h"


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


bool openInputFile(std::ifstream& _inFile, std::string _path);
bool dropLineIntoBuffer(std::ifstream& _inFile, double* _buffer);

void testSegmentation(){
	std::cout << "TESTING SEGMENTATION ALGORITHM && EKF" << std::endl;
	cv::Mat img, ori;

	std::string path = "";

	#if defined (_linux)
		path = "/home/bardo91/Programming/Images/";
	#endif
	#if defined (_WIN32)
		path = "C:/Programming/Imagenes Stereo Tracking/P1_640x480/Images/";	
	#endif
	
	std::cout << "Path of images: " << path << std::endl;

	bool condition = true;
	int i = 0;

	std::cout << "Init Timer" << std::endl;
	BOViL::STime::init();

	BOViL::STime *time = BOViL::STime::get();

	double t0, t1;

	std::cout << "Create Clustered Space" << std::endl;
	BOViL::ColorClusterSpace *cs = BOViL::CreateHSVCS_8c(255U,255U, std::uint8_t(BOViL::bin2dec("00010000")));

	//-------
	std::cout << "Init Stereo EKF" << std::endl;
	BOViL::algorithms::StereoVisionEKF stereoEKF;

	stereoEKF.setUpEKF(	BOViL::math::Matrix<double>(arrayQ, 6, 6),
						BOViL::math::Matrix<double>(arrayR, 4, 4),
						BOViL::math::Matrix<double>(arrayX0, 6, 1));

	stereoEKF.setUpCameras(738.143358488352310, 346.966835812843040 , 240.286986071815390);
	double inputBuffer[20];
	std::ifstream inputFile;
	
	std::cout << "Open Input File" << std::endl;
	condition = openInputFile(inputFile, "C:/Programming/Imagenes Stereo Tracking/P1_640x480/ViconData2.txt");

	while(condition){

		//t0 = time->frameTime();

		// ----------------- IMAGE SEGMENTATION ------------------------
		++i;
		std::stringstream ss;

		ss << path;
		ss << "img";
		ss << i;
		ss << "_cam1.jpg";

		std::string imagePath = "HOLA";
		
		imagePath = ss.str();

		img = cv::imread(imagePath, CV_LOAD_IMAGE_COLOR);

		img.copyTo(ori);

		t0 = time->frameTime();
		std::vector<BOViL::ImageObject> objects;

		cv::cvtColor(img, img, CV_BGR2HSV);

		BOViL::algorithms::ColorClustering<std::uint8_t>(	img.data,		// Image pointer
															img.cols,		// Width
															img.rows,		// Height
															5,				// Size Threshold
															objects,		// Output Objects
															*cs);			// Segmentation function 
														


		//BOVIL::algorithms::ColorClustering<std::uint8_t>(	img.data,		// Image pointer
		//													img.cols,		// Width
		//													img.rows,		// Height
		//													5,				// Size Threshold
		//													objects,		// Output Objects
		//													[](unsigned char *_a, unsigned char *_b, unsigned char *_c){	if(*_a < 80 && *_b < 80 && *_c > 180){
		//																														*_a = 0;
		//																														*_b = 0;
		//																														*_c = 255;
		//																														return 4;
		//																													} else{
		//																														*_a = 0;
		//																														*_b = 0;
		//																														*_c = 0;
		//																														return -1;
		//																													}
		//																													});	// Segmentation function
		
		t1 = time->frameTime();

		std::cout << 1/(t1-t0) << " fps" << std::endl;
		std::cout << "Number of detected Objects in the scene: " << objects.size() << std::endl;

		#ifdef _DEBUG
	
		for(unsigned int obj = 0; obj < objects.size() ; obj++){
			BOViL::Point2ui p = objects[obj].getCentroid();
			cv::circle(ori, cv::Point2d(p.x,p.y), objects[obj].getHeight()/2, cv::Scalar(1,1,1), 1);
		}

		cv::imshow("ORIGINAL", ori);
		#endif
		// ----------------- TRACKING ALGORITHM ------------------------
		dropLineIntoBuffer(inputFile, inputBuffer);		// Get objects info.
		// Update cameras pos and ori
		double arrayPosC1[3] = {inputBuffer[7], inputBuffer[8], inputBuffer[9]};
		double arrayPosC2[3] = {inputBuffer[13], inputBuffer[14], inputBuffer[15]};
		stereoEKF.updateCameras(BOViL::math::Matrix<double>(arrayPosC1, 3, 1),
								BOViL::math::Matrix<double>(arrayPosC2, 3, 1),	
								BOViL::algorithms::createRotationMatrixEuler(inputBuffer[10], inputBuffer[11], inputBuffer[12]),
								BOViL::algorithms::createRotationMatrixEuler(inputBuffer[16], inputBuffer[17], inputBuffer[18]));
		// Select Oject
		int maxSize = 0, maxIndex = 0;
		for(unsigned int obj = 0; obj < objects.size() ; obj++){
			if(objects[obj].getSize() > maxSize){
				maxSize = objects[obj].getSize();
				maxIndex = obj;
			}
		}

		double arrayZk[4] = {objects[i].getCentroid().x, objects[i].getCentroid().y, 5.2, 6.3};
		stereoEKF.stepEKF(BOViL::math::Matrix<double>(arrayZk, 4, 1),inputBuffer[0]);
		
		cv::waitKey(1);

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