/*
 * ColorSpaceHSV8.h
 *
 *  Created on: Oct 28, 2013
 *      Author: pablo
 */

#ifndef _OPENBIL_COLORSPACEHSV8_H_
#define _OPENBIL_COLORSPACEHSV8_H_

#include "ColorClusterSpace.h"

#include <math.h>
#include <string>

namespace BIL {
	namespace algorithms {
		uint8_t bin2dec(std::string bin);

		ColorClusterSpace<unsigned char> *CreateHSVCS_8c(uint8_t, uint8_t, uint8_t);
		ColorClusterSpace<float> *CreateHSVCS_fc(uint8_t, uint8_t, uint8_t);

	} // namespace segmentation.
} // namespace vision.

#endif // _OPENBIL_COLORSPACEHSV8_H_
