/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-24
//
/////////////////////////////////////////////////////////////////////////////////////////



#include "LinearSubspace.h"

namespace BOViL	{
	namespace math{
		//-------------------------------------------------------------------------------------
		LinearSubspace::LinearSubspace():	
									mDimension(0),
									mSpaceDimensión(0)	{

		}
		//-------------------------------------------------------------------------------------
		LinearSubspace::LinearSubspace(Matrix<double> &_matrixEcuations, Matrix<double> &_vectorCoef) :
									mMatrixEcuations(_matrixEcuations),
									mVectorIndepCoef(_vectorCoef),
									mDimension(_matrixEcuations.getHeight()),
									mSpaceDimensión(_matrixEcuations.getWidth())	{

			assert(_vectorCoef.getHeight() == _matrixEcuations.getHeight());
			
		}
		
		//-------------------------------------------------------------------------------------
		int LinearSubspace::getDimension(){
			return mDimension;
		
		}

		//-------------------------------------------------------------------------------------
		int LinearSubspace::getDimensionContainer(){
			return mSpaceDimensión;

		}
		//-------------------------------------------------------------------------------------


		//-------------------------------------------------------------------------------------
	}	//	namespace geometrics
}	//	namespace BOViL