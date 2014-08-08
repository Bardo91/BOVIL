/////////////////////////////////////////////////////////////////////////////////////////
//
//		BOVIL: test image segmentation
//			Author: Pablo Ramon Soria
//			Date:	2014-08-08
//
/////////////////////////////////////////////////////////////////////////////////////////
// Segmentator

#include "Segmentator.h"

#include <algorithms/segmentation/ColorClustering.h>

using namespace BOViL::algorithms;
using namespace cv;

namespace test{
	//-----------------------------------------------------------------------------------
	bool Segmentator::segmentateImage(const Mat &_srcImg, Mat &_dstImg, std::vector<BOViL::ImageObject> &_objects){
		if (_srcImg.rows == 0)
			return false;
		
		_srcImg.copyTo(_dstImg);

		ColorClustering<uchar>(_dstImg.data, _dstImg.cols, _dstImg.rows, colorThreshold, _objects, *ccs);

		return true;
	};

	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
}	//	namespace test