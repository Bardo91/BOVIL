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



using namespace test;
using namespace cv;
using namespace BOViL;
using namespace std;

map<string, string> parseArgs(int _argc, char** _argv);
void singleImage(Segmentator &_segmentator, map<string, string> &_hashMap);
void multipleImages(Segmentator &_segmentator, map<string, string> &_hashMap);

int main(int _argc, char** _argv){

	map<string, string> hashMap = parseArgs(_argc, _argv);

	ColorClusterSpace *ccs = CreateHSVCS_8c(255U, 255U, 255U);

	test::Segmentator segmentator(ccs, 100);

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

	cvtColor(ori, ori, CV_BGR2HSV);
	if (_segmentator.segmentateImage(ori, seg, objects)){
		cout << "Hecho" << endl;
		cvtColor(seg, seg, CV_HSV2BGR);
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
		if (ori.rows != 0){
			cvtColor(ori, ori, CV_BGR2HSV);
			_segmentator.segmentateImage(ori, seg, objects);
			cvtColor(seg, seg, CV_HSV2BGR);
			imshow("image", seg);
			waitKey(1);
		}
		else
			condition = false;
		
		i++;
	}


}