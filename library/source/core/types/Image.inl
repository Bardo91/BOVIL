/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		OpenBOVIL
//			Author: Pablo Ramon Soria
//			Date:	2014-10-14
/////////////////////////////////////////////////////////////////////////////////////////
// Inline implementation of template Image

#include <cassert>

template<typename Type_, unsigned width_, unsigned height_, unsigned channels_>
Image<Type_, width_, height_, channels_>::Image(){

}

//---------------------------------------------------------------------------------------------------------------------
template<typename Type_, unsigned width_, unsigned height_, unsigned channels_>
Image<Type_, width_, height_, channels_>::Image(std::string _imgPath){
	if (!isFreeImageInitialized){
		initFreeImage();
	}

	eImageTypes type = checkImageType(_imgPath);
	assert(type != eImageTypes::ERROR);	//	 Filetype not supported yet

	FIBITMAP * imageFI = FreeImage_Load((FREE_IMAGE_FORMAT) type, _imgPath.c_str());
	
	Type_* data = (Type_ *) FreeImage_GetBits(imageFI);
	data;

}
//---------------------------------------------------------------------------------------------------------------------
template<typename Type_, unsigned width_, unsigned height_, unsigned channels_>
void Image<Type_, width_, height_, channels_>::loadImage(std::string _imgPath){
	_imgPath;
}
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------

