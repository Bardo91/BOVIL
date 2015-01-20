/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-05-12
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "algorithms/segmentation/ColorClustering.h"
#include "core/types/ColorSpaceHSV8.h"
#include "core/time/time.h"
#include "algorithms/state_estimators/GroundTrackingEKF.h"

#include <SOIL.h>

#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>

struct QuadState{
	double eulerAngles[3];
	double position[3];
};

typedef std::function <QuadState(double *)> QuadParser;

void testSegmentation(std::string _filePath, std::function<std::string(unsigned int)> _nameGen, QuadParser _parser);
