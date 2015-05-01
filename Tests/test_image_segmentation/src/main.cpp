/////////////////////////////////////////////////////////////////////////////////////////
//
//		BOVIL: test image segmentation
//			Author: Pablo Ramon Soria
//			Date:	2014-08-08
//
/////////////////////////////////////////////////////////////////////////////////////////
// main


#include "Segmentator.h"

#include <iostream>
#include <sstream>

#include <algorithms/segmentation/color_clustering/types/ColorSpaceHSV8.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>

#include <algorithms/segmentation/color_clustering/types/ccsCreation.h>


using namespace test;
using namespace cv;
using namespace BOViL;
using namespace std;

map<string, string> parseArgs(int _argc, char** _argv);
void singleImage(Segmentator &_segmentator, map<string, string> &_hashMap);
void multipleImages(Segmentator &_segmentator, map<string, string> &_hashMap);

int main(int _argc, char** _argv){

	map<string, string> hashMap = parseArgs(_argc, _argv);

	ColorClusterSpace ccs = createSingleClusteredSpace(0, 180, 0, 70, 180, 255, 180, 255, 255, 36);

	test::Segmentator segmentator(&ccs, 100);

	if (!strcmp(hashMap["TYPE"].c_str(), "SINGLE")){
		singleImage(segmentator, hashMap);
	}
	if (!strcmp(hashMap["TYPE"].c_str(), "MULTI")){
		multipleImages(segmentator, hashMap);
	}
	
	
}


map<string, string> parseArgs(int _argc, char** _argv){
	map<string, string> hashMap;
	for (int i = 1; i < _argc; i++){
		string arg(_argv[i]);
		size_t next = arg.find_first_of('=');
		string type = arg.substr(0, next);
		arg = arg.substr(next + 1, arg.size());
		hashMap[type] = arg;
		cout << "Detected argument: " << type << " - With value: " << arg << endl;
	}
	return hashMap;
}


void singleImage(Segmentator &_segmentator, map<string, string> &_hashMap){
	Mat seg, ori = imread(_hashMap["IMG_PATH"]);

	vector<BOViL::ImageObject> objects;
	ori.copyTo(seg);
	cvtColor(seg, seg, CV_BGR2HSV);
	if (_segmentator.segmentateImage(seg, objects)){
		cout << "Hecho" << endl;
		cvtColor(seg, seg, CV_HSV2BGR);
		hconcat(ori, seg, seg);
		imshow("image", seg);
		waitKey(1);
	}
	else
		cout << "Error" << endl;

	system("PAUSE");

}

void multipleImages(Segmentator &_segmentator, map<string, string> &_hashMap){
	stringstream ss;

	int i = 160;
	bool condition = true;

	Mat ori, seg;

	vector<ImageObject> objects;

	while (condition){
		stringstream ss;
		ss << _hashMap["IMG_PATH"];
		ss << i;
		ss << ".jpg";

		ori = imread(ss.str());
		ori.copyTo(seg);
		objects.clear();
		if (ori.rows != 0){
			cvtColor(seg, seg, CV_BGR2HSV);
			_segmentator.segmentateImage(seg, objects);
			cvtColor(seg, seg, CV_HSV2BGR);

			for (ImageObject object : objects){
				circle(ori, Point2i(object.getCentroid().x, object.getCentroid().y), object.getWidth() / 2, Scalar(255, 255, 255), 3);
			}

			hconcat(ori, seg, seg);
			imshow("image", seg);
			waitKey(1);
		}
		else
			condition = false;
		
		i++;
	}


}