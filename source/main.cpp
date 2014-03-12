///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

<<<<<<< HEAD
#include <opencv/cv.h>
#include <opencv/cv.hpp>
#include <opencv/highgui.h>

#include <iostream>

#include "algorithms/segmentation/ColorClustering.h"
#include "core/types/ColorSpaceHSV8.h"
=======
#include <sstream>
#include <string>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "algorithms/segmentation/ColorClustering.h"
#include "core/types/ColorSpaceHSV8.h"
#include "core/math/Matrix.h"

#include "core/time/time.h"
>>>>>>> 2b981b1b56e27612f9bbd1398f52973083f4eef0

int main(void){
	
	std::cout << "TESTING MATRIX OPERATIONS" << std::endl;

	BOViL::math::Matrix<double> mat(3,3);

	std::cout << "TESTING SEGMENTATION ALGORITHM" << std::endl;
	cv::Mat img, ori;

	std::string path = "C:/Programming/Imagenes Stereo Tracking/P1_640x480/Images/";

	int i = 0;


	BOViL::STime::init();

	BOViL::STime *time = BOViL::STime::get();

	double t0, t1;

<<<<<<< HEAD
	std::cout << "Rows: " << img.rows << " - Cols: " << img.cols << std::endl;

	img.copyTo(ori);
=======
	while(1){
>>>>>>> 2b981b1b56e27612f9bbd1398f52973083f4eef0

		t0 = time->frameTime();

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

		std::vector<BOViL::ImageObject> objects;

		BOViL::ColorClusterSpace *cs = BOViL::CreateHSVCS_8c(255U,255U,BOViL::bin2dec("00010000"));

		cv::cvtColor(img, img, CV_BGR2HSV);

		BOViL::algorithms::ColorClustering<unsigned char>(	img.data,		// Image pointer
															img.cols,		// Width
															img.rows,		// Height
															5,				// Size Threshold
															objects,		// Output Objects
															*cs);			// Segmentation function 
														

<<<<<<< HEAD
	//BOVIL::algorithms::ColorClustering<unsigned char>(	img.data,		// Image pointer
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

	for(unsigned int i = 0; i < objects.size() ; i++){
		BOVIL::Point p = objects[i].getCentroid();
		cv::circle(ori, cv::Point2i(p.x,p.y), objects[i].getHeight()/2, cv::Scalar(1,1,1), 1);
	}

	delete cs;

	cv::imshow("IMAGEORI", ori);
	cv::imshow("Segmentated", img);
=======
		//BOVIL::algorithms::ColorClustering<unsigned char>(	img.data,		// Image pointer
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

		for(unsigned int i = 0; i < objects.size() ; i++){
			BOViL::Point p = objects[i].getCentroid();
			cv::circle(ori, cv::Point2i(p.x,p.y), objects[i].getHeight()/2, cv::Scalar(1,1,1), 1);
		}
		cv::imshow("IMAGEORI", ori);
		cv::imshow("Segmentated", img);

		cv::waitKey(1);

		t1 = time->frameTime();

		std::cout << "Step takes: " << t1-t0 << " s" << std::endl;
>>>>>>> 2b981b1b56e27612f9bbd1398f52973083f4eef0

	}
	cv::waitKey();
<<<<<<< HEAD


=======
	
>>>>>>> 2b981b1b56e27612f9bbd1398f52973083f4eef0

	return 0;

}
