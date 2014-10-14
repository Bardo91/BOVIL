/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		OpenBOVIL
//			Author: Pablo Ramon Soria
//			Date:	2014-10-14
/////////////////////////////////////////////////////////////////////////////////////////
//

#include "Image.h"
#include <cassert>

namespace BOViL{
	//---------------------------------------------------------------------------------------------------------------------
	// Static data initialization
	bool Image::isFreeImageInitialized = false;

	//---------------------------------------------------------------------------------------------------------------------
	void Image::initFreeImage(){
			FreeImage_Initialise(true);
			isFreeImageInitialized = true;
	}

	//---------------------------------------------------------------------------------------------------------------------
	Image::Image(std::string _imgPath){
		assert(loadImage(_imgPath));
	}

	//---------------------------------------------------------------------------------------------------------------------
	bool Image::loadImage(std::string _imgPath){
		if (!isFreeImageInitialized){
			initFreeImage();
		}
		FIBITMAP *imageFI = FreeImage_Load(FreeImage_GetFileType(_imgPath.c_str()), _imgPath.c_str());
		if (nullptr == imageFI)
			return false;

		mData = FreeImage_GetBits(imageFI);
		mWidth = FreeImage_GetWidth(imageFI);
		mHeight = FreeImage_GetHeight(imageFI);
		mPitch = FreeImage_GetPitch(imageFI);

		return true;
	}

	//---------------------------------------------------------------------------------------------------------------------
	bool Image::saveImage(std::string _imgPath){
		if (!isFreeImageInitialized){
			initFreeImage();
		}
		
		return false;

	}

	//---------------------------------------------------------------------------------------------------------------------
}