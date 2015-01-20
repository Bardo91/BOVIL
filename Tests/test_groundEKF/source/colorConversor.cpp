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


Terna RGB2HSV(Terna _terna);

bool colorConversor(eCcTypes _type, unsigned char *_image, unsigned _width, unsigned _height, unsigned _channels){
	std::function < Terna(Terna) > conversor;

	switch (_type) {
	case eRGB2HSV:
		break;
	default:
		break;
	}


	return true;
}
