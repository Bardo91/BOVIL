/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: 
//
//		Author: Pablo Ramon Soria
//		Date:	2015-01-20
//
/////////////////////////////////////////////////////////////////////////////////////////
// Color Conversor


enum eCcTypes {eRGB2HSV = 0};


struct Terna{
	unsigned a, b, c;
	Terna() :a(0), b(0), c(0){};
	Terna(unsigned _a, unsigned _b, unsigned _c){
		a = _a; b = _b; c = _c;
	};
};


bool colorConversor(eCcTypes _type, unsigned char *_image, unsigned _width, unsigned _height, unsigned _channels);
