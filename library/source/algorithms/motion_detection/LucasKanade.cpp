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
		float* lucasKanade(unsigned char * _image1, unsigned char * _image2, unsigned _width, unsigned _height, unsigned _windowSize){
			assert(_windowSize % 2 == 1);	// Window size must be odd
			
			// Struct to acces easily to images.
			ImageHandle image1(_image1, _width, _height);
			ImageHandle image2(_image2, _width, _height);

			// Allocate array for velocities.
			float *result = new float[_width*_height/_windowSize/_windowSize * 2];

			MatrixXf Ixs(_width, _height);
			MatrixXf Iys(_width, _height);
			MatrixXf Its(_width, _height);
			// Calculate derivatives.
			// Ix = [-1, 0, 1]*I(x-1:x+1, y)
			// Iy = [-1, 0, 1]*I(x, y-1:y+1)
			// It = [-1, 1]*[I(t)-I(t-1)]
			for (unsigned i = 1; i < _height - 1; i++){
				for (unsigned j = 1 ; j < _width - 1; j++){
					Ixs(i, j) = -image1(i - 1, j) + image1(i + 1, j);
					Iys(i, j) = -image1(i, j - 1) + image1(i, j + 1);
					Its(i, j) = image2(i, j) - image1(i, j);
				}
			}

			// Calc Speed. Supposed windowSize  == 3.
			for (unsigned i = 1; i < _height - 1; i = i + 3){
				for (unsigned j = 1; j < _width - 1; j = j + 3){
					MatrixXd spatialDeriv(3, 2);
					Vector3d temporalDeriv;
					
					Matrix2d velocities = spatialDeriv.jacobiSvd(ComputeThinU | ComputeThinV).solve(temporalDeriv);
				}
			}

			return result;
			
		}
	}	//	namespace algorithms
}	//	namespace BOViL