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

#include <string>
#include <FreeImage.h>

namespace BOViL{
	static bool isFreeImageInitialized = false;

	void initFreeImage();

	enum class eImageTypes { ERROR = 0, JPG = FIF_JPEG, PNG = FIF_PNG };

	eImageTypes checkImageType(std::string _imgPath);

	template<typename Type_, unsigned width_, unsigned height_, unsigned channels_>
	struct Image{
		typedef Type_ mType;
		Image();
		Image(std::string _imgPath);

		void loadImage(std::string _imgPath);

		const unsigned width(){ return width_; };
		const unsigned height(){ return height_; };
		const unsigned channels(){ return channels_; };

	private:
		mType mData[width_*height_*channels_];

	};

	#include "Image.inl"

}	//	namespace BOViL

#endif	//	_BOVIL_CORE_TYPES_IMAGE_H_