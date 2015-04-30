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
#include <iostream>

using namespace Eigen;

namespace BOViL{
	namespace algorithms{
		// Simple unweighted Lucas Kanade algorithm.
		float* lucasKanade(float * _result, unsigned char * _image1, unsigned char * _image2, unsigned _width, unsigned _height, unsigned _windowSize){
			assert(_windowSize % 2 == 1);	// Window size must be odd
			
			// Struct to acces easily to images.
			ImageHandle image1(_image1, _width, _height);
			ImageHandle image2(_image2, _width, _height);

			// Allocate array for velocities.
			float *result = new float[_width*_height/_windowSize/_windowSize * 2];

			MatrixXf Ixs(_height, _width);
			MatrixXf Iys(_height, _width);
			MatrixXf Its(_height, _width);
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
			Ixs = Ixs / 255;
			//std::cout << Ixs/255 << std::endl;
			memcpy(_result, Ixs.data(), sizeof(_result));

			return nullptr;

			/*
			// Calc Speed. Supposed windowSize  == 3.
			for (unsigned i = 1; i < _height - 1; i = i + 3){
				for (unsigned j = 1; j < _width - 1; j = j + 3){
					MatrixXf spatialDeriv(9, 2);
					spatialDeriv <<		Ixs(i-1, j-1),	Iys(i-1, j-1),
										Ixs(i-1, j),	Iys(i-1, j),
										Ixs(i-1, j+1),	Iys(i-1, j+1);
										Ixs(i, j-1),	Iys(i, j-1);
										Ixs(i, j),		Iys(i, j);
										Ixs(i, j+1),	Iys(i, j+1);
										Ixs(i+1, j-1),	Iys(i+1, j);
										Ixs(i+1, j),	Iys(i+1, j);
										Ixs(i+1, j+1),	Iys(i+1, j);

					VectorXf temporalDeriv(9);
					temporalDeriv <<	Its(i - 1, j - 1),
										Its(i - 1, j),
										Its(i - 1, j + 1),
										Its(i, j - 1),
										Its(i, j),
										Its(i, j + 1),
										Its(i + 1, j - 1),
										Its(i + 1, j),
										Its(i + 1, j + 1);
					
					Vector2f velocities = spatialDeriv.jacobiSvd(ComputeThinU | ComputeThinV).solve(temporalDeriv);
				}
			}

			return result;
			*/
		}
	}	//	namespace algorithms
}	//	namespace BOViL