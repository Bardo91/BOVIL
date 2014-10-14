/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		OpenBOVIL
//			Author: Pablo Ramon Soria
//			Date:	2014-10-14
/////////////////////////////////////////////////////////////////////////////////////////
//

#include "Image.h"

namespace BOViL{
	//---------------------------------------------------------------------------------------------------------------------
	eImageTypes checkImageType(std::string _imgPath){
		unsigned index = _imgPath.find_last_of('.');

		std::string format = _imgPath.substr(index + 1, _imgPath.length());

		if (format.compare("jpg") || format.compare("jpeg")){
			return eImageTypes::JPG;
		}
		else if (format.compare("png")){
			return eImageTypes::PNG;
		}

		return eImageTypes::ERROR;

	}
	//---------------------------------------------------------------------------------------------------------------------
	void initFreeImage(){
			FreeImage_Initialise(true);
			isFreeImageInitialized = false;
	}
	//---------------------------------------------------------------------------------------------------------------------
}