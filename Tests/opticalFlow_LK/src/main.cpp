///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Lucas Kanade 
//			Author:	Pablo Ramon Soria (a.k.a. Bardo91)
//			Date:	2015-APR-14
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include <algorithms/motion_detection/LucasKanade.h>
#include <core/time/time.h>
#include <iostream>

#include <opencv2/opencv.hpp>

int main(int _argc, char ** _argv){
	_argc; _argv;

	BOViL::STime *timer = BOViL::STime::get();
	// Load images.
	
	cv::Mat im1;
	cv::cvtColor(cv::imread("C:/programming/datasets/opticalflow/eval-data/Army/frame10.png"), im1, cv::COLOR_RGB2GRAY);
	cv::Mat im2;
	cv::cvtColor(cv::imread("C:/programming/datasets/opticalflow/eval-data/Army/frame11.png"), im2, cv::COLOR_RGB2GRAY);

	// Procces pair of images.
	float * result = new float[im1.cols*im1.rows];
		
	double t0 = timer->getTime();
	BOViL::algorithms::lucasKanade(result, im1.data, im2.data, im1.cols, im1.rows, 3);
	double t1 = timer->getTime();


	cv::Mat gradX(im1.rows, im1.cols, CV_32FC1, result);
	cv::imshow("gradX", gradX);

	/*for (int i = 0; i < im1.rows / 3; i++){
		for (int j = 0; j < im1.cols / 3; i++){
			cv::Point2d p1(i*3*im1.cols, j*3);
			cv::Point2d p2(i * 3 * im1.cols + result[i*im1.rows / 3 + j], j * 3 + result[i*im1.rows / 3 + j+ 1]);
			cv::line(im1, p1, p2, cv::Scalar(255, 255, 255));
		}
	}*/

	cv::imshow("res", im1);

	std::cout << "Spent " << t1 - t0 << " seconds" << std::endl;
	cv::waitKey();
}
