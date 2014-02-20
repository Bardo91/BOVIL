///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _OPENBIL_COLORS_H_
#define _OPENBIL_COLORS_H_

#include <type_traits>

namespace BIL{
	// ----- Types and structures -----
	template<typename T_> struct color3 {
			color3(){
				a = b = c = T_(0);
			};
			color3(T_ _a, T_ _b, T_ _c){
				a = _a; b = _b; c = _c;
			};
			
			T_ a, b, c;
		};

	typedef color3<unsigned char> c3u;

	// ----- Functions -----
	
	// 666 TODO: Hacer traits y dejarlo molon, pero ahora hay prisa
	c3u PixelBGR2HSV(c3u _color);
}


#endif	//_OPENBIL_COLORS_H_