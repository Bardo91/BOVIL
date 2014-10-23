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
		assert(load(_imgPath));
	}

	//---------------------------------------------------------------------------------------------------------------------
	bool Image::load(std::string _imgPath){
		if (!isFreeImageInitialized){
			initFreeImage();
		}
		FIBITMAP *imageFI = FreeImage_Load(FreeImage_GetFileType(_imgPath.c_str()), _imgPath.c_str());
		if (nullptr == imageFI)
			return false;

		FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(imageFI);	// 666 TODO: only standart RGBA bitmap is supported
		assert(imageType == FIT_BITMAP);

		mData		= FreeImage_GetBits(imageFI);
		mWidth		= FreeImage_GetWidth(imageFI);
		mHeight		= FreeImage_GetHeight(imageFI);
		mPitch		= FreeImage_GetPitch(imageFI);
		mBPP		= FreeImage_GetBPP(imageFI);
		mRedMask	= FreeImage_GetRedMask(imageFI);
		mGreenMask	= FreeImage_GetGreenMask(imageFI);
		mBlueMask	= FreeImage_GetBlueMask(imageFI);

		return true;
	}

	//---------------------------------------------------------------------------------------------------------------------
	bool Image::save(std::string _imgPath){
		if (!isFreeImageInitialized){
			initFreeImage();
		}

		FIBITMAP *image = FreeImage_ConvertFromRawBits(mData, mWidth, mHeight, mPitch, mBPP, mRedMask, mGreenMask, mBlueMask);

		if (FreeImage_Save(FreeImage_GetFileType(_imgPath.c_str()), image, _imgPath.c_str()))
			return true;
		else
			return false;

	}

	//---------------------------------------------------------------------------------------------------------------------
}