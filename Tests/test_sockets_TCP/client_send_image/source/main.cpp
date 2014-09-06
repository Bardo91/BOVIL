///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Image Sender
//		Author:	Pablo Ramon Soria
//		Date:	2014-09-05
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//



//---------------------------------------------------------------------------------------------------------------------
#include <core/comm/Socket.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <string>

//---------------------------------------------------------------------------------------------------------------------
using namespace cv;
using namespace BOViL::comm;
using namespace std;


#include "CameraSource.h"
#include "ImageProcessor.h"

//---------------------------------------------------------------------------------------------------------------------
int main(){

	CameraSource cameraSource;
	ImageProcessor imageProcessor;

	cameraSource.registerListener(imageProcessor);


	//Mat img = imread("c:/Tulips.jpg");
	//
	//Socket* clientSocket = Socket::createSocket(eSocketType::clientTCP, "5028", "localhost");
	//
	//string msg((const char *)img.data);
	//
	//clientSocket->sendMsg(msg);
	//
	//volatile bool condition = true;
	//while (condition){
	//	
	//}

}