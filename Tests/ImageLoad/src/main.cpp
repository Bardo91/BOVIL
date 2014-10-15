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

	double midCV = 0;
	double midFI = 0;

	for (int i = 0; i < 100; i++){
		double t0 = time->getTime();
		Image img("C:/Tulips.jpg");
		double t1 = time->getTime();
		Mat imageCV = imread("C:/Tulips.jpg");
		double t2 = time->getTime();
		
		midCV += t2 - t1;
		midFI += t1 - t0;
		std::cout << i << " ";
	}
	std::cout << std::endl;

	midCV = midCV / 100;
	midFI = midFI / 100;

	std::cout << "My time: " << midFI << std::endl;
	std::cout << "CV time: " << midCV << std::endl;

	system("PAUSE");

}