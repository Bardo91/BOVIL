///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Image Sender
//		Author:	Pablo Ramon Soria
//		Date:	2014-09-06
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Image Processor



#ifndef _IMG_SENDER_IMAGE_PROCESSOR_H_
#define _IMG_SENDER_IMAGE_PROCESSOR_H_

#include "CameraSource.h"

class extractedInfo;

class ImageProcessor{
public:
	void operator()(const ImageDescriptor &_frame);	//	 Event to be registered in CameraSource
	void registerListener(std::function<void(const extractedInfo &)>);

private:
	bool processImage();

private:
	ImageDescriptor mCurrentFrame;
	std::vector < std::function<void(const extractedInfo &)>> mListeners;

};


#endif	//	_IMG_SENDER_IMAGE_PROCESSOR_H_
