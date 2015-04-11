///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	
//	BOVIL: 
//		Author: Pablo Ramón Soria
//		Date:	2015-APR-09
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


#ifndef BOVIL_ALGORITHMS_FILTERING_CONVOLUTION_H_
#define BOVIL_ALGORITHMS_FILTERING_CONVOLUTION_H_

#include <array>

#include "Kernels.h"

namespace BOViL{
	namespace algorithms{
		template<typename PixelType_, unsigned KernelSize_>
		void imageConvolution(	PixelType_*			_image,
								unsigned					_width,
								unsigned					_height,
								unsigned					_channels,
								Kernel<KernelSize_>			_kernel){
			static_assert(double(KernelSize_) / 2 != 0.5, "Kernels need to be odd");

			PixelType_ *res = new PixelType_[_width*_height*_channels];

			const int midKernelSize = int(KernelSize_) / 2;

			for (unsigned col = midKernelSize + 1; col < _width - midKernelSize; col++) {
				for (unsigned row = midKernelSize + 1; row < _height - midKernelSize; row++){
					for (unsigned channel = 0; channel < _channels; channel++){
						// Extract subimage
						std::array<double, KernelSize_ * KernelSize_> subImage;
						memset(subImage.data(), 0, KernelSize_*KernelSize_);
						for (int i = -midKernelSize; i <= midKernelSize; i++){
							for (int j = -midKernelSize; j <= midKernelSize; j++){
								unsigned pixelIndex = row*_width*_channels + col*_channels + channel;
								subImage[i*(KernelSize_) + j] = _image[pixelIndex + i*_width*_channels + j*_channels];
							}
						}
						//Convolute subimage with kernel
						res[row*_width*_channels + col*_channels + channel] = static_cast<unsigned char>(convolute<double, KernelSize_>(subImage, _kernel));
					}
				}
			}
			PixelType_ *auxPointerHolder = _image;
			_image = res;
			res = nullptr;
			delete[] auxPointerHolder;
		}

		template<typename Type_, unsigned Size_>
		Type_ convolute(std::array<Type_, Size_ * Size_> _kernel1, std::array<Type_, Size_ * Size_> _kernel2){
			Type_ res = 0;
			for (unsigned i = 0; i < Size_*Size_; i++){
				res += _kernel1[i] * _kernel2[i];
			}
			return res;
		}
	}	//	namespace algorithms
}	//	namespace BOViL

#endif	//	BOVIL_ALGORITHMS_FILTERING_CONVOLUTION_H_