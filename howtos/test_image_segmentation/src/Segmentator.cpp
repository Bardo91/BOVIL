/////////////////////////////////////////////////////////////////////////////////////////
//
//		BOVIL: test image segmentation
//			Author: Pablo Ramon Soria
//			Date:	2014-08-08
//
/////////////////////////////////////////////////////////////////////////////////////////
// Segmentator

#include "Segmentator.h"

#include <algorithms/segmentation/color_clustering/ColorClustering.h>

using namespace BOViL::algorithms;
using namespace cv;

namespace test{
	//-----------------------------------------------------------------------------------
	bool Segmentator::segmentateImage(const Mat &_srcImg, std::vector<BOViL::ImageObject> &_objects){
		if (_srcImg.rows == 0)
			return false;
	

		ColorClustering<uchar>(_srcImg.data, _srcImg.cols, _srcImg.rows, colorThreshold, _objects, *ccs);

		return true;
	};

	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------
}	//	namespace test