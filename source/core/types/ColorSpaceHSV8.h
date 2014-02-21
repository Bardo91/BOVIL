/*
 * ColorSpaceHSV8.h
 *
 *  Created on: Oct 28, 2013
 *      Author: pablo
 */

#ifndef _BOVIL_COLORSPACEHSV8_H_
#define _BOVIL_COLORSPACEHSV8_H_

#include "ColorClusterSpace.h"

#include <math.h>
#include <string>

namespace BOVIL {
	uint8_t bin2dec(std::string bin);

	ColorClusterSpace *CreateHSVCS_8c(unsigned char _maskH, unsigned char _maskS, unsigned char _maskV);
} // namespace vision.

#endif // _BOVIL_COLORSPACEHSV8_H_
