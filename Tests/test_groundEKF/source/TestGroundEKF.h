/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-12
//
/////////////////////////////////////////////////////////////////////////////////////////


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

#include "algorithms/state_estimators/GroundTrackingEKF.h"

#include <cstdint>
#include <fstream>
#include <string>

void testSegmentation(std::string _filePath, std::function<std::string(unsigned int)> _nameGen);
