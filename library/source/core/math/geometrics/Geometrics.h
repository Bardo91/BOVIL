/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-05
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_CORE_GEOMETRICS_GEOMETRIC_H_
#define _BOVIL_CORE_GEOMETRICS_GEOMETRIC_H_


namespace BOViL{
	namespace geometrics{
		class SubSpace;	

		class Transformation;	
		
		//-------------------------------------------------------------------------------------
		void rotationEulerMatrix(float _alpha, float _beta, float _gamma, double * _matrix);		/// Euler Matrix rotation given as an array

	}	// namespace geometrics

}	// namespace BOViL


#endif	//_BOVIL_CORE_GEOMETRICS_GEOMETRIC_H_