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


void testSegmentation(){
	BOViL::algorithms::StereoVisionEKF stereoEKF;

	stereoEKF.setUpEKF(	BOViL::math::Matrix<double>(arrayQ, 6, 6),
						BOViL::math::Matrix<double>(arrayR, 4, 4),
						BOViL::math::Matrix<double>(arrayX0, 6, 1));

	stereoEKF.setUpCameras(738.143358488352310, 346.966835812843040 , 240.286986071815390);
	double inputBuffer[20];
	
	while(1){
		// ----------------- TRACKING ALGORITHM ------------------------
		// Update cameras pos and ori
		double arrayPosC1[3] = {9.6,5.5,56.5};
		double arrayPosC2[3] = {9.6,5.5,56.5};
		stereoEKF.updateCameras(BOViL::math::Matrix<double>(arrayPosC1, 3, 1),
								BOViL::math::Matrix<double>(arrayPosC2, 3, 1),	
								BOViL::algorithms::createRotationMatrixEuler(9.6,5.5,56.5),
								BOViL::algorithms::createRotationMatrixEuler(9.6,5.5,56.5));
		
		double arrayZk[4] = {9.6, 5.5, 5.2, 6.3};
		stereoEKF.stepEKF(BOViL::math::Matrix<double>(arrayZk, 4, 1),inputBuffer[0]);
		
		cv::waitKey(1);

	}

	std::cout << "----------End----------" << std::endl;
}
