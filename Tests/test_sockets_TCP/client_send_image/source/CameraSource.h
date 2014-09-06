///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Image Sender
//		Author:	Pablo Ramon Soria
//		Date:	2014-09-06
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Camera Source

#ifndef _IMG_SENDER_CAMERA_SOURCE_H_
#define _IMG_SENDER_CAMERA_SOURCE_H_


#include <functional>
#include <mutex>
#include <thread>

#include <vector>

#include <opencv2/opencv.hpp>

const unsigned int IMAGE_ROWS = 128;
const unsigned int IMAGE_COLS = 128;
const unsigned int IMAGE_CHANNELS = 3;

class ImageDescriptor{
public:
	ImageDescriptor(){}
	~ImageDescriptor(){ delete mData; }

	unsigned int mRows = IMAGE_ROWS;
	unsigned int mCols = IMAGE_ROWS;
	unsigned int mChannels = IMAGE_CHANNELS;
	unsigned char *mData = new unsigned char[IMAGE_ROWS * IMAGE_COLS];

};


class CameraSource{
public:
	CameraSource();

	const ImageDescriptor getFrame();			// Get the last frame acquired from the camera
	void registerListener(std::function<void(const ImageDescriptor &)> _listener);	// Register a new listener waiting for new frames

	void startCapture();
	void stopCapture();

private:
	void update();

private:
	volatile bool mIsCapturing = false;

	ImageDescriptor mCurrentFrame;
	std::vector<std::function<void(const ImageDescriptor &)>> mListeners;
	cv::VideoCapture mImageSource;


	std::thread mCaptureThread;
	std::mutex mCaptureMutex;
};


#endif	//	_IMG_SENDER_CAMERA_SOURCE_H_