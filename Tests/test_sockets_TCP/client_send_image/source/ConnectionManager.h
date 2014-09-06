///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Image Sender
//		Author:	Pablo Ramon Soria
//		Date:	2014-09-05
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


#ifndef _IMG_SENDER_CONNECTION_MANAGER_H_
#define _IMG_SENDER_CONNECTION_MANAGER_H_

#include "ImageProcessor.h">
#include <vector>

class ConnectionManager{
public:
	ConnectionManager();
	void operator()(const ImageDescriptor &_frame);	//	 Event to be registered in CameraSource

private:


private:
	
};

#endif	//	_IMG_SENDER_CONNECTION_MANAGER_H_