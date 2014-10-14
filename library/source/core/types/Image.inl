/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		OpenBOVIL
//			Author: Pablo Ramon Soria
//			Date:	2014-10-14
/////////////////////////////////////////////////////////////////////////////////////////
// Inline implementation of template Image

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

	FIBITMAP * imageFI = FreeImage_Load(type, _imgPath.c_str());

	mData = (Type_ *)FreeImage_GetBits(imageFI);

}
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------

