/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-12
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "TestSegmentation.h"
#include "algorithms\state_estimators\StereoVisionEKF.h"

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

	int i = 0;

	BOViL::STime::init();

	BOViL::STime *time = BOViL::STime::get();

	double t0, t1;

	BOViL::ColorClusterSpace *cs = BOViL::CreateHSVCS_8c(255U,255U,BOViL::bin2dec("00010000"));

	BOViL::algorithms::StereoVisionEKF stereoEKF;

	stereoEKF.setUpCameras(738.143358488352310, 346.966835812843040 , 240.286986071815390);

	while(1){

		t0 = time->frameTime();

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

		std::vector<BOViL::ImageObject> objects;

		cv::cvtColor(img, img, CV_BGR2HSV);

		BOViL::algorithms::ColorClustering<unsigned char>(	img.data,		// Image pointer
															img.cols,		// Width
															img.rows,		// Height
															5,				// Size Threshold
															objects,		// Output Objects
															*cs);			// Segmentation function 
														


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
		
		t1 = time->frameTime();

		std::cout << 1/(t1-t0) << " fps" << std::endl;

		#ifdef _DEBUG
		for(unsigned int i = 0; i < objects.size() ; i++){
			BOViL::Point2ui p = objects[i].getCentroid();
			cv::circle(ori, cv::Point2d(p.x,p.y), objects[i].getHeight()/2, cv::Scalar(1,1,1), 1);
		}

		cv::imshow("ORIGINAL", ori);
		#endif

		// ----------------- TRACKING ALGORITHM ------------------------

		cv::waitKey(1);

	}

}