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

#include "algorithms/segmentation/ColorClustering.h"
#include "core/types/ColorSpaceHSV8.h"
#include "core/math/Matrix.h"

#include "../../../../library/source/core/comm/ClientSocket.h"

#include "core/time/time.h"

#include "algorithms/state_estimators/StereoVisionEKF.h"

#include <cstdint>
#include <fstream>



void testSegmentation(BOViL::comm::ClientSocket *_client, int _id, std::string _path);
