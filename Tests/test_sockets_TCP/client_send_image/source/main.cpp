///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Image Sender
//		Author:	Pablo Ramon Soria
//		Date:	2014-09-05
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//



//---------------------------------------------------------------------------------------------------------------------
#include <string>

//---------------------------------------------------------------------------------------------------------------------
using namespace std;


#include "CameraSource.h"
#include "ImageProcessor.h"

//---------------------------------------------------------------------------------------------------------------------
int main(){

	CameraSource cameraSource;
	ImageProcessor imageProcessor;

	cameraSource.registerListener(imageProcessor);

	cameraSource.startCapture();

	for (;;){

	}

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