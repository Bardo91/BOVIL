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



namespace BOViL{
	template<typename Type_, unsigned width_, unsigned height_, unsigned channels_>
	struct Image{
		typedef Type_ mType;

		const unsigned width(){ return width_; };
		const unsigned height(){ return height_; };
		const unsigned channels(){ return channels_; };

	private:
		mType mData[width_*height_*channels_];
	};


}	//	namespace BOViL

#endif	//	_BOVIL_CORE_TYPES_IMAGE_H_