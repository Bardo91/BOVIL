///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Image Sender
//		Author:	Pablo Ramon Soria
//		Date:	2014-09-06
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Image Processor


//---------------------------------------------------------------------------------------------------------------------
#include "ImageProcessor.h"

using namespace std;
using namespace cv;
//---------------------------------------------------------------------------------------------------------------------
void ImageProcessor::operator()(const ImageDescriptor &_frame){
	memcpy(mCurrentFrame.mData, _frame.mData, _frame.mCols * _frame.mRows * _frame.mChannels);

}

//---------------------------------------------------------------------------------------------------------------------
void ImageProcessor::registerListener(std::function<void(const extractedInfo &)>){

}

//---------------------------------------------------------------------------------------------------------------------
void ImageProcessor::startProcessing(){
	mIsProcessing = true;

	mProcessThread = thread([this](){
		while (mIsProcessing){
			processImage();
		}
	});

}

//---------------------------------------------------------------------------------------------------------------------
void ImageProcessor::stopProcessing(){
	mIsProcessing = false;

	assert(mProcessThread.joinable());
	mProcessThread.join();

}

//---------------------------------------------------------------------------------------------------------------------
bool ImageProcessor::processImage(){
	mProcessMutex.lock();
	Mat image(mCurrentFrame.mRows, mCurrentFrame.mCols, CV_8UC3, mCurrentFrame.mData);
	mProcessMutex.unlock();

	imshow("image", image);

	return false;
}

//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------


