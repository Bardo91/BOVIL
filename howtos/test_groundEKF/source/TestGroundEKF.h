/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-12
//
/////////////////////////////////////////////////////////////////////////////////////////

#include <algorithms/state_estimators/GroundTrackingEKF.h>
#include <algorithms/segmentation/ColorClustering.h>
#include <core/types/ColorSpaceHSV8.h>
#include <core/types/Colors.h>
#include <core/time/time.h>

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <SOIL.h>
#include <string>
#include <sstream>

struct QuadState{
	double eulerAngles[3];
	double position[3];
};

typedef std::function <QuadState(double *)> QuadParser;

void testSegmentation(std::string _filePath, std::function<std::string(unsigned int)> _nameGen, QuadParser _parser);