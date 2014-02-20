////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Color Cluster Segmentation Stereo Tracking
//
//		Author: Pablo Ramón Soria
//		Date: 2013/10/22
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Color Cluster Space
//		Here is defined the limits of every color and functions to truncate colors.

#include "ColorSpaceHSV8.h"

namespace BIL {
	namespace algorithms {
		unsigned char bin2dec(std::string bin) {
			const char *cstr = bin.c_str();
			int len, dec = 0, i, exp;

			len = strlen(cstr);
			exp = len - 1;

			for (i = 0; i < len; i++, exp--)
				dec += cstr[i] == '1' ? int(pow(2, exp)) : 0;
			return unsigned char(dec);
		}

		ColorClusterSpace *CreateHSVCS_8c(unsigned char MaskH, unsigned char MaskS, unsigned char MaskV) {

			unsigned char HClass[36];
			unsigned char SClass[36];
			unsigned char VClass[36];

			for (int i = 0; i < 36; i++) {
				HClass[i] = bin2dec(HClassStr8[i]) & MaskH;
				SClass[i] = bin2dec(SClassStr8[i]) & MaskS;
				VClass[i] = bin2dec(VClassStr8[i]) & MaskV;
			}

			return new ColorClusterSpace(36, HClass, SClass, VClass, colorsHSV8);

		}
	} // namespace segmentation
} // namespace vision
