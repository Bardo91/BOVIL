/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: ImageLoad Test
//
//		OpenBOVIL
//			Author: Pablo Ramon Soria
//			Date:	2014-10-14
/////////////////////////////////////////////////////////////////////////////////////////
//
#include <core/time/time.h>
#include <core/types/Image.h>
#include <iostream>

#include <opencv/cv.h>
#include <opencv/highgui.h>



using namespace BOViL;
using namespace cv;

int main(){	

	STime::init();
	STime *time = STime::get();

	double t0 = time->getTime();
	Image img("C:/Tulips.jpg");
	double t1 = time->getTime();
	Mat imageCV = imread("C:/Tulips.jpg");
	double t2 = time->getTime();

	std::cout << "My time: " << t1 - t0 << std::endl;
	std::cout << "CV time: " << t2 - t1 << std::endl;

	system("PAUSE");

}