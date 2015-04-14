///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL:	Lucas Kanade
//			Author:	Pablo Ramon Soria (a.k.a. Bardo91)
//			Date:	2015-APR-14
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include "LucasKanade.h"

namespace BOViL{
	namespace algorithms{
		void lucasKanade(unsigned char * _image1, unsigned char * _image2, unsigned _width, unsigned _height, unsigned _kernelSize){
			// Struct to acces easily to images
			ImageHandle image1(_image1, _width, _height);
			ImageHandle image2(_image2, _width, _height);

			
			for (unsigned i = 0; i < _height; i++){
				for (unsigned j = 0; j < _width; j++){

				}
			}

			
		}
	}	//	namespace algorithms
}	//	namespace BOViL