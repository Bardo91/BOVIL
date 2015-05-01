/////////////////////////////////////////////////////////////////////////////////////////
//
//		BOVIL: test image segmentation
//			Author: Pablo Ramon Soria
//			Date:	2014-08-08
//
/////////////////////////////////////////////////////////////////////////////////////////
// Segmentator



#ifndef _BOVIL_TEST_IMAGE_SEGMENTATION_SEGMENTATOR_H_
#define _BOVIL_TEST_IMAGE_SEGMENTATION_SEGMENTATOR_H_

#include <core/types/BasicTypes.h>
#include <algorithms/segmentation/color_clustering/types/ColorClusterSpace.h>
#include <opencv2/core/core.hpp>

namespace test{
	class Segmentator{
	public:
		Segmentator(BOViL::ColorClusterSpace *_ccs, const int _colorThreshold){ ccs = _ccs; colorThreshold = _colorThreshold; };
	public:
		bool segmentateImage(const cv::Mat &_srcImg, cv::Mat &_dstImg, std::vector<BOViL::ImageObject> &_objects);
		void changeCCS(BOViL::ColorClusterSpace *_ccs){ ccs = _ccs; };
		void changeThreshold(const int _colorThreshold){ colorThreshold = _colorThreshold; };

	private:
		BOViL::ColorClusterSpace *ccs;
		int colorThreshold;

	};


}	//	namespace test

#endif