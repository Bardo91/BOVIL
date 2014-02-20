///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

#include "Colors.h"

#include <math.h>
#include <stdint.h>
#include <string>

#ifndef _OPENBIL_COLORCLUSTERSPACE_H_
#define _OPENBIL_COLORCLUSTERSPACE_H_

#define LOG2 0.3010299957

namespace BIL{
	namespace algorithms {
		class ColorClusterSpace {
		public:
			int size;
			c3u *clusters;
			ColorClusterSpace(int, unsigned char *, unsigned char *, unsigned char *, const c3u *);
			~ColorClusterSpace();

		private:
			unsigned char *AClass;
			unsigned char *BClass;
			unsigned char *CClass;

		public:
			int operator()(unsigned char *_a, unsigned char *_b, unsigned char *_c){
				c3u col(*_a, *_b, *_c);

				int color =  whichColor(col);	
				if(color != -1){
					*_a = clusters[color].a;
					*_b = clusters[color].b;
					*_c = clusters[color].c;
				} else{
					*_a = 0U;
					*_b = 0U;
					*_c = 0U;
				}

				return color;
			};

			int whichColor(c3u&); // Return between 0 and 255

		};


		inline int ColorClusterSpace::whichColor(c3u& color) { // If Opencv gives YCrCb values between 0 and 255

			int i = (color.a * (size - 1) / 180); // 666 TODO: improve (get 5%)
			int j = color.b*(size - 1) >> 7;
			j = (j>>1) + (j&1);
			int k = color.c*(size - 1) >> 7;
			k = (k>>1) + (k&1);
			

			int res = AClass[i] & BClass[j] & CClass[k]; //Supposing that colors are not over-layed there's only one possible solution and log2(x) returns an integer /

			int aux = 0;

			if (!res)
				return -1;

			while (!(res & 0x01)) {
				res = res >> 1;
				aux += 1;
			}

			return aux;
		}



	} // namespace algorithms.
} // namespace BIL.
#endif // _OPENBIL_COLORCLUSTERSPACE_H_
