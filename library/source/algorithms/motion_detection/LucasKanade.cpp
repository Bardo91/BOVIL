///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL:	Lucas Kanade
//			Author:	Pablo Ramon Soria (a.k.a. Bardo91)
//			Date:	2015-APR-14
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include "LucasKanade.h"
#include <Eigen/Eigen>

using namespace Eigen;

namespace BOViL{
	namespace algorithms{
		// Simple unweighted Lucas Kanade algorithm.
		void lucasKanade(unsigned char * _image1, unsigned char * _image2, unsigned _width, unsigned _height, unsigned _windowSize){
			assert(_windowSize % 2 == 1);	// Window size must be odd
			
			// Struct to acces easily to images.
			ImageHandle image1(_image1, _width, _height);
			ImageHandle image2(_image2, _width, _height);

			// Allocate array for velocities.
			float *result = new float[_width*_height * 2];

			// Star the algorithm.
			for (unsigned i = 1 + _windowSize; i < _height - 1 - _windowSize; i = i + _windowSize){
				for (unsigned j = 1 + _windowSize; j < _width - 1 - _windowSize; j = + _windowSize){
					MatrixXd spatialDerivatives(_windowSize*_windowSize, 2);
					MatrixXd temporalDerivatives(_windowSize*_windowSize, 1);

					// Compute derivatives.
					for (int subI = -int(_windowSize)/2; subI < _windowSize/2; subI++){
						for (int subJ = -int(_windowSize)/2; subJ < _windowSize/2; subJ++){
							spatialDerivatives((subI + _windowSize / 2) * _windowSize + (subJ + _windowSize / 2), 0) = image2(i + subI - 1, j + subJ) - image2(i + subI + 1, j + subJ);
							spatialDerivatives((subI + _windowSize / 2)	* _windowSize + (subJ + _windowSize / 2), 1) = image2(i + subI, j + subJ - 1) - image2(i + subI, j + subJ + 1);
							temporalDerivatives((subI + _windowSize / 2)	* _windowSize + (subJ + _windowSize / 2)) = image2(i + subI, j + subJ) - image1(i + subI, j + subJ);
						}
					}

					// Calculate velocity in pixel (i,j).
					MatrixXd velocities = (spatialDerivatives.transpose() * spatialDerivatives).inverse() * spatialDerivatives.transpose() * temporalDerivatives;
					result[i*_width + j + 0] = velocities(0);
					result[i*_width + j + 1] = velocities(1);
				}
			}

			
		}
	}	//	namespace algorithms
}	//	namespace BOViL