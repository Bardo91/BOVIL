/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: 
//
//		Author: Pablo Ramon Soria
//		Date:	2015-01-20
//
/////////////////////////////////////////////////////////////////////////////////////////
// Color Conversor


#include "colorConversor.h"

#include <functional>


TernaU RGB2HSV(TernaU _terna);

bool colorConversor(eCcTypes _type, unsigned char *_image, unsigned _width, unsigned _height, unsigned _channels){
	std::function < TernaU(TernaU) > conversor;

	switch (_type) {
	case eRGB2HSV:
		conversor = RGB2HSV;
		break;
	default:
		break;
	}

	for (unsigned i = 0; i < _height; i++){
		for (unsigned j = 0; j < _width; j++){
			TernaU t = conversor(TernaU(	_image[_width*_channels*i + _channels*j + 0],
											_image[_width*_channels*i + _channels*j + 1],
											_image[_width*_channels*i + _channels*j + 2]));

			_image[_width*_channels*i + _channels*j + 0] = t.a;
			_image[_width*_channels*i + _channels*j + 1] = t.b;
			_image[_width*_channels*i + _channels*j + 2] = t.c;
		}
	}

	return true;
}

template<typename TypeIn_, typename TypeOut_>
TypeOut_ MAX(TypeIn_ _a, TypeIn_ _b, TypeIn_ _c){
	return _a > _b ? (_a > _c ? _a : _c) : (_b > _c ? _b : _c);
}

template<typename TypeIn_, typename TypeOut_>
TypeOut_ MIN(TypeIn_ _a, TypeIn_ _b, TypeIn_ _c){
	return _a < _b ? (_a < _c ? _a : _c) : (_b < _c ? _b : _c);
}

TernaU RGB2HSV(TernaU _terna){

	TernaD hsv;
	double min, max, delta;
	min = MIN<unsigned, double>(_terna.a, _terna.b, _terna.c);
	max = MAX<unsigned, double>(_terna.a, _terna.b, _terna.c);
	hsv.c = max;				// v
	delta = max - min;
	if (max != 0)
		hsv.b = delta / max;		// s
	else {
		// r = g = b = 0		// s = 0, v is undefined
		hsv.b = 0;
		hsv.a = -1;
		return;
	}
	if (_terna.a == max)
		hsv.a = (_terna.b - _terna.c) / delta;		// between yellow & magenta
	else if (_terna.b == max)
		hsv.a = 2 + (_terna.c - _terna.a) / delta;	// between cyan & yellow
	else
		hsv.a = 4 + (_terna.a - _terna.b) / delta;	// between magenta & cyan
	hsv.a *= 60;				// degrees
	if (hsv.a < 0)
		hsv.a += 360;

	return TernaU(unsigned(hsv.a/360*255), unsigned(hsv.b*255), unsigned(hsv.c*255));
}