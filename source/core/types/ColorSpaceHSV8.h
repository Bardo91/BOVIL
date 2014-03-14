/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ramon Soria
//		Date:	2014-05-03
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_COLORSPACEHSV8_H_
#define _BOVIL_COLORSPACEHSV8_H_

#include "ColorClusterSpace.h"

#include <math.h>
#include <string>

namespace BOViL {
	uint8_t bin2dec(std::string bin);

	ColorClusterSpace *CreateHSVCS_8c(unsigned char _maskH, unsigned char _maskS, unsigned char _maskV);
} // namespace BOViL.

#endif // _BOVIL_COLORSPACEHSV8_H_
