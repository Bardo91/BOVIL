///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOVIL Test: image convolution
//			Author:	Pablo R.S.
//			Date:	2015-APR-09
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main

#include <SOIL.h>

#include <algorithms/filtering/Convolution.h>

int main(){
	int width, height, channels;
	unsigned char *image = SOIL_load_image ( "c:/Tulips.jpg", &width, &height, &channels, SOIL_LOAD_AUTO);

	BOViL::algorithms::imageConvolution<unsigned char, 3>(image, width, height, channels, BOViL::algorithms::blur);

	SOIL_save_image("./blurred.jpg", SOIL_SAVE_TYPE_DDS, width, height, channels, image);
}
