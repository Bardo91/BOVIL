/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-05-12
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "TestSegmentation.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>

bool openInputFile(std::ifstream& _inFile, std::string _path);
bool dropLineIntoBuffer(std::ifstream& _inFile, double* _buffer);

void testSegmentation(BOViL::comm::ClientSocket *_client, int _id, std::string _path){
	std::cout << "TESTING SEGMENTATION ALGORITHM && EKF" << std::endl;
	cv::Mat img, ori;

	std::string path = "";
	
	std::cout << "--Path of images: " << _path << std::endl;

	bool condition = true;
	int i = 0;

	std::cout << "--Init Timer" << std::endl;
	BOViL::STime::init();

	BOViL::STime *time = BOViL::STime::get();

	double t0, t1;

	std::cout << "--Create Clustered Space" << std::endl;
	BOViL::ColorClusterSpace *cs = BOViL::CreateHSVCS_8c(255U,255U, std::uint8_t(BOViL::bin2dec("00010000")));

	while(condition){

		//t0 = time->frameTime();

		// ----------------- IMAGE SEGMENTATION ------------------------
		++i;
		std::stringstream ss;

		ss << _path << "img" << i << "_cam" << _id << ".jpg";
		

		std::string imagePath = ss.str();
		std::cout << imagePath << std::endl;
		img = cv::imread(imagePath, CV_LOAD_IMAGE_COLOR); //cv::imread(imagePath, CV_LOAD_IMAGE_COLOR);

		img.copyTo(ori);

		t0 = time->getTime();
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
		
		t1 = time->getTime();
		double fps = 1/(t1-t0);
		std::cout << fps << " fps" << std::endl;
		std::cout << "Number of detected Objects1 in the scene: " << objects.size() << std::endl;

		std::stringstream ssMsg;

		for (unsigned int i = 0; i < objects.size(); i++){
			ssMsg << objects[i].getCentroid().x << ";" << objects[i].getCentroid().y << "\n";
		}

		_client->sendData(ssMsg.str());

			
		cv::waitKey(1);

	}

	std::cout << "----------End----------" << std::endl;

	_client->sendData("QUIT");
}
