/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: 
//
//		Author: Pablo Ramon Soria
//		Date:	2015-01-20
//
/////////////////////////////////////////////////////////////////////////////////////////
// Color Conversor


enum eCcTypes {eRGB2HSV = 0};

template<typename Type_>
struct Terna{
	Type_ a, b, c;
	Terna() :a(0), b(0), c(0){};
	Terna(Type_ _a, Type_ _b, Type_ _c){
		a = _a; b = _b; c = _c;
	};
};

typedef Terna<unsigned> TernaU;
typedef Terna<unsigned char> TernaUC;
typedef Terna<double> TernaD;


bool colorConversor(eCcTypes _type, unsigned char *_image, unsigned _width, unsigned _height, unsigned _channels);
