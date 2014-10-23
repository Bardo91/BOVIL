/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		OpenBOVIL
//			Author: Pablo Ramon Soria
//			Date:	2014-10-14
/////////////////////////////////////////////////////////////////////////////////////////
//



#ifndef _BOVIL_CORE_TYPES_IMAGE_H_
#define _BOVIL_CORE_TYPES_IMAGE_H_


#include <dshow.h>
#include <string>
//#include <FreeImage.h>
#include "../../../external_deps/FreeImage/include/FreeImage.h"

namespace BOViL{
	struct Image{
		Image();
		Image(std::string _imgPath);

		bool load(std::string _imgPath);
		bool save(std::string _imgPath);

		const unsigned width(){ return mWidth; };
		const unsigned height(){ return mHeight; };
		const unsigned pitch(){ return mPitch; };

		unsigned char & operator[](unsigned _index){ return mData[_index]; };
	private:
		unsigned char	*mData		= nullptr;
		unsigned		mWidth		= 0;
		unsigned		mHeight		= 0;
		unsigned		mPitch		= 0;
		unsigned		mBPP		= 0;
		unsigned		mRedMask	= 0;
		unsigned		mGreenMask	= 0;
		unsigned		mBlueMask	= 0;

	private:
		static bool isFreeImageInitialized;
		void initFreeImage();

	};


}	//	namespace BOViL

#endif	//	_BOVIL_CORE_TYPES_IMAGE_H_