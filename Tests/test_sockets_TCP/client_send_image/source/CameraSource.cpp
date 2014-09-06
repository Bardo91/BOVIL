///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Image Sender
//		Author:	Pablo Ramon Soria
//		Date:	2014-09-06
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Camera Source


#include <cassert>
#include <iostream>

#include "CameraSource.h"

const unsigned int CAM_SOURCE = 0;

using namespace cv;
using namespace std;

//---------------------------------------------------------------------------------------------------------------------
CameraSource::CameraSource(){
	mImageSource.open(CAM_SOURCE);

	if (!mImageSource.isOpened()){
		std::cout << "LOG: Can't open image source" << std::endl;
		assert(false);
	}
	mImageSource.set(CV_CAP_PROP_FRAME_WIDTH, IMAGE_COLS);
	mImageSource.set(CV_CAP_PROP_FRAME_HEIGHT, IMAGE_ROWS);

}

//---------------------------------------------------------------------------------------------------------------------
const ImageDescriptor CameraSource::getFrame(){
	return mCurrentFrame;

}

//---------------------------------------------------------------------------------------------------------------------
void CameraSource::registerListener(std::function<void(const ImageDescriptor &)> _listener){
	mCaptureMutex.lock();
	mListeners.push_back(_listener);	// Add listener to the list
	mCaptureMutex.unlock();

}

//---------------------------------------------------------------------------------------------------------------------
void CameraSource::startCapture(){
	mIsCapturing = true;

	mCaptureThread = thread([this](){
		while (mIsCapturing){
			update();
		}
	});

}

//---------------------------------------------------------------------------------------------------------------------
void CameraSource::stopCapture(){
	mIsCapturing = false;

	assert(mCaptureThread.joinable());
	mCaptureThread.join();

}

//---------------------------------------------------------------------------------------------------------------------
void CameraSource::update(){
	Mat frame;
	mImageSource >> frame;

	memcpy(mCurrentFrame.mData, frame.data, IMAGE_COLS * IMAGE_ROWS * IMAGE_CHANNELS);

	for (function<void(const ImageDescriptor &)> listener : mListeners){
		listener(mCurrentFrame);
	}
	
}

//---------------------------------------------------------------------------------------------------------------------


