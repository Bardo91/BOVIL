/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: ImageLoad Test
//
//		OpenBOVIL
//			Author: Pablo Ramon Soria
//			Date:	2014-10-14
/////////////////////////////////////////////////////////////////////////////////////////
//

#include <core/types/Image.h>

using namespace BOViL;

int main(){
	
	FIBITMAP * image = FreeImage_Load(FIF_JPEG,"C:/Tulips.jpg");

	unsigned size = FreeImage_GetRedMask(image);

	if (size == FI16_555_RED_MASK){
		
	}
	size;
	system("PAUSE");

}