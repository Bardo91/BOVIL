///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Lucas Kanade 
//			Author:	Pablo Ramon Soria (a.k.a. Bardo91)
//			Date:	2015-APR-14
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include <SOIL.h>
#include <algorithms/motion_detection/LucasKanade.h>

struct ImageData{
	unsigned char* data;
	int width, height, channels;
};

int main(int _argc, char ** _argv){

	// Load images.
	ImageData image1, image2;

	image1.data = SOIL_load_image("", &image1.width, &image1.height, &image1.channels, SOIL_LOAD_AUTO);
	image2.data = SOIL_load_image("", &image2.width, &image2.height, &image2.channels, SOIL_LOAD_AUTO);

	// Procces pair of images.


}