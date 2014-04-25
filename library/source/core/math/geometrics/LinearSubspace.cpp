/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-04-24
//
/////////////////////////////////////////////////////////////////////////////////////////



#include "LinearSubspace.h"

namespace BOViL	{
	namespace math{
		//-------------------------------------------------------------------------------------
		LinearSubspace::LinearSubspace():	
									mDimension(0),
									mSpaceDimensi�n(0)	{

		}
		//-------------------------------------------------------------------------------------
		LinearSubspace::LinearSubspace(Matrix<double> &_matrixEcuations, Matrix<double> &_vectorCoef) :
									mMatrixEcuations(_matrixEcuations),
									mVectorIndepCoef(_vectorCoef),
									mDimension(_matrixEcuations.getHeight()),
									mSpaceDimensi�n(_matrixEcuations.getWidth())	{

			assert(_vectorCoef.getHeight() == _matrixEcuations.getHeight());
			
		}
		
		//-------------------------------------------------------------------------------------
		int LinearSubspace::getDimension(){
			return mDimension;
		
		}

		//-------------------------------------------------------------------------------------
		int LinearSubspace::getDimensionContainer(){
			return mSpaceDimensi�n;

		}
		//-------------------------------------------------------------------------------------


		//-------------------------------------------------------------------------------------
	}	//	namespace geometrics
}	//	namespace BOViL