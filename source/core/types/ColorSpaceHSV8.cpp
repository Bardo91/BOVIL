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
		const c3u colorsHSV8[8] = {
		/*Black*/	c3u(0, 0, 0),
		/*White*/	c3u( 0, 0, 255 ),
		/*Blue*/	c3u( 120, 255, 255 ),
		/*Purple*/	c3u( 150, 255, 255 ),
		/*Red*/		c3u( 0, 255, 255 ),
		/*Orange*/	c3u( 15, 255, 255 ),
		/*Yellow*/	c3u( 30, 255, 255 ),
		/*Green*/	c3u( 60, 255, 255 ) };

		const color3<float> colorsHSVf[8] = {
		/*Black*/	color3<float>(0.0f, 0.0f, 0.0f),
		/*White*/	color3<float>( 0.0f, 0.0f, 1.0f ),
		/*Blue*/	color3<float>( 0.47f, 1.0f, 1.0f ),
		/*Purple*/	color3<float>( 0.59f, 1.0f, 1.0f ),
		/*Red*/		color3<float>( 0, 1.0f, 1.0f ),
		/*Orange*/	color3<float>( 0.058f, 1.0f, 1.0f ),
		/*Yellow*/	color3<float>( 0.117f, 1.0f, 1.0f ),
		/*Green*/	color3<float>( 0.2353f, 1.0f, 1.0f ) };


		

		const std::string HClassStr8[36] = { "00010011", "00010011", "00100011",
				"00100011", "00100011", "01000011", "01000011", "10000011", "10000011",
				"10000011", "10000011", "10000011", "10000011", "10000011", "10000011",
				"10000011", "00000111", "00000111", "00000111", "00000111", "00000111",
				"00000111", "00000111", "00000111", "00000111", "00000111", "00000111",
				"00000111", "00001011", "00001011", "00001011", "00001011", "00001011",
				"00001011", "00010011", "00010011" };
		const std::string SClassStr8[36] = { "00000011", "00000011", "00000011",
				"00000011", "00000011", "00000011", "00000011", "00000011", "00000011",
				"11111101", "11111101", "11111101", "11111101", "11111101", "11111101",
				"11111101", "11111101", "11111101", "11111101", "11111101", "11111101",
				"11111101", "11111101", "11111101", "11111101", "11111101", "11111101",
				"11111101", "11111101", "11111101", "11111101", "11111101", "11111101",
				"11111101", "11111101", "11111101" };
		const std::string VClassStr8[36] = { "00000001", "00000001", "00000001",
				"00000001", "00000001", "00000001", "00000001", "00000001", "11111110",
				"11111110", "11111110", "11111110", "11111110", "11111110", "11111110",
				"11111110", "11111110", "11111110", "11111110", "11111110", "11111110",
				"11111110", "11111110", "11111110", "11111110", "11111110", "11111110",
				"11111110", "11111110", "11111110", "11111110", "11111110", "11111110",
				"11111110", "11111110", "11111110" };


		unsigned char bin2dec(std::string bin) {
			const char *cstr = bin.c_str();
			int len, dec = 0, i, exp;

			len = strlen(cstr);
			exp = len - 1;

			for (i = 0; i < len; i++, exp--)
				dec += cstr[i] == '1' ? int(pow(2, exp)) : 0;
			return unsigned char(dec);
		}

		ColorClusterSpace<unsigned char> *CreateHSVCS_8c(unsigned char MaskH, unsigned char MaskS, unsigned char MaskV) {

			unsigned char HClass[36];
			unsigned char SClass[36];
			unsigned char VClass[36];

			for (int i = 0; i < 36; i++) {
				HClass[i] = bin2dec(HClassStr8[i]) & MaskH;
				SClass[i] = bin2dec(SClassStr8[i]) & MaskS;
				VClass[i] = bin2dec(VClassStr8[i]) & MaskV;
			}

			return new ColorClusterSpace<unsigned char>(36, HClass, SClass, VClass, colorsHSV8);

		}

		ColorClusterSpace<float> *CreateHSVCS_fc(unsigned char MaskH, unsigned char MaskS, unsigned char MaskV) {

			float HClass[36];
			float SClass[36];
			float VClass[36];

			for (int i = 0; i < 36; i++) {
				HClass[i] = float((bin2dec(HClassStr8[i]) & MaskH)/255.0f);
				SClass[i] = float((bin2dec(SClassStr8[i]) & MaskS)/255.0f);
				VClass[i] = float((bin2dec(VClassStr8[i]) & MaskV)/255.0f);
			}

			return new ColorClusterSpace<float>(36, HClass, SClass, VClass, colorsHSVf);

		}

	} // namespace segmentation
} // namespace vision
