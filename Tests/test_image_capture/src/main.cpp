/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramon Soria
//		Date:	2014-05-06
//
/////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>


#include <opencv2/highgui/highgui.hpp>

std::map<std::string, std::string> parseArgs(int _argc, char** _argv);

int main(int _argc, char** _argv){
	std::map<std::string, std::string> hashMap = parseArgs(_argc, _argv);

	int option = atoi(hashMap["OPTION"].c_str());

	cv::Mat img;

	cv::VideoCapture cam(0);

	if (cam.isOpened()){
		cam >> img;
		
		if (option == 0){

			cv::imshow("test", img);
		}
		else if (option == 1){
			cv::imwrite("./testImage.jpg", img);

		}
	}else{
		assert(false);
	}

	return 0;
}

std::map<std::string, std::string> parseArgs(int _argc, char** _argv){
	std::map<std::string, std::string> hashMap;
	for (int i = 1; i < _argc; i++){
		std::string arg(_argv[i]);
		size_t next = arg.find_first_of('=');
		std::string type = arg.substr(0, next);
		arg = arg.substr(next + 1, arg.size());
		hashMap[type] = arg;
		std::cout << "Detected argument: " << type << " - With value: " << arg << std::endl;
	}
	return hashMap;
}
