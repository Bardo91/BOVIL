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
		template <int spaceSize_, int subspaceSize_>
		LinearSubspace::LinearSubspace():	
									mDimension(0),
									mSpaceDimensión(0)	{

		}
		//-------------------------------------------------------------------------------------
		template <int spaceSize_, int subspaceSize_>
		LinearSubspace::LinearSubspace(Matrix<double> &_matrixEcuations, Matrix<double> &_vectorCoef) :
									mMatrixEcuations(_matrixEcuations),
									mVectorIndepCoef(_vectorCoef)	{

			assert(_vectorCoef.getHeight() == _matrixEcuations.getHeight());
			
		}
		
		//-------------------------------------------------------------------------------------
		template <int spaceSize_, int subspaceSize_>
		int LinearSubspace::getDimensionSpace(){
			return mSpaceSize;
		
		}

		//-------------------------------------------------------------------------------------
		template <int spaceSize_, int subspaceSize_>
		int LinearSubspace::getDimensionSubspace(){
			return mSubspaceSize;

		}
		//-------------------------------------------------------------------------------------
		template <int spaceSize_, int subspaceSice_>
		int LinearSubspace::checkSubspace(){


		}

		//-------------------------------------------------------------------------------------
	}	//	namespace geometrics
}	//	namespace BOViL