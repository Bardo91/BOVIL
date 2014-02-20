///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

#include "Colors.h"

namespace BIL {
	c3u PixelBGR2HSV(c3u _color){
		c3u HSV;
		unsigned char MAX, MIN;

		_color.a > _color.b ? (_color.a > _color.c ? MAX = _color.a : MAX = _color.c) : (_color.b > _color.c ? MAX = _color.b : MAX = _color.c);
		_color.a < _color.b ? (_color.a < _color.c ? MIN = _color.a : MIN = _color.c) : (_color.b < _color.c ? MIN = _color.b : MIN = _color.c);
	

		if(MAX == MIN)
			HSV.a = 0;
		else if (_color.c == MAX && _color.b >= _color.a)
			HSV.a = 60*(_color.b - _color.a)/(MAX - MIN)/2 + 0U;
		else if (_color.c == MAX && _color.b < _color.a)
			HSV.a = 60*(_color.b - _color.a)/(MAX - MIN)/2 + 180;
		else if (_color.b == MAX)
			HSV.a = 60*(_color.a - _color.c)/(MAX - MIN)/2 + 60U;
		else if (_color.a == MAX)
			HSV.a = 60*(_color.c - _color.b)/(MAX - MIN)/2 + 120U;
		
		// OpenCV H = [0, 180];

		MAX == 0 ? HSV.b = 0 : HSV.b = 1 - MIN/MAX;
		
		HSV.c = MAX;
		
		return HSV;
	}

}