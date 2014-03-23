/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-12
//
/////////////////////////////////////////////////////////////////////////////////////////

#if defined (_linux)
	#include <opencv/cv.hpp>
#endif
#include <opencv/highgui.h>

#include <iostream>

#include "algorithms/segmentation/ColorClustering.h"
#include "core/types/ColorSpaceHSV8.h"

#include <sstream>
#include <string>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "algorithms/segmentation/ColorClustering.h"
#include "core/types/ColorSpaceHSV8.h"
#include "core/math/Matrix.h"

#include "core/time/time.h"

#include "algorithms\state_estimators\StereoVisionEKF.h"

#include <cstdint>
#include <fstream>

void testSegmentation();