///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

#include <opencv\cv.h>
#include <opencv\highgui.h>

#include "algorithms\segmentation\ColorClustering.h"
#include "core\types\ColorSpaceHSV8.h"

int main(void){

	cv::Mat img, ori;

	img = cv::imread("../../test.jpg", CV_LOAD_IMAGE_COLOR);

	img.copyTo(ori);

	std::vector<BIL::ImageObject> objects;

	BIL::algorithms::ColorClusterSpace *cs = BIL::algorithms::CreateHSVCS_8c(255U,255U,BIL::algorithms::bin2dec("00010000"));

	cv::cvtColor(img, img, CV_BGR2HSV);
	
	BIL::algorithms::ColorClustering<uchar>(	img.data,		// Image pointer
												img.cols,		// Width
												img.rows,		// Height
												5,				// Size Threshold
												objects,		// Output Objects
												*cs);	// Segmentation function

	//BIL::algorithms::ColorClustering<unsigned char>(	img.data,		// Image pointer
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
		BIL::Point p = objects[i].getCentroid();
		cv::circle(ori, cv::Point2i(p.x,p.y), objects[i].getHeight()/2, cv::Scalar(1,1,1), 1);
	}
	cv::imshow("IMAGEORI", ori);
	cv::imshow("Segmentated", img);

	cv::waitKey();
	
	delete cs;


	return 0;

}