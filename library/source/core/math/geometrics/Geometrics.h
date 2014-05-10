/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-05-03
//
/////////////////////////////////////////////////////////////////////////////////////////


#include "../Matrix.h"
#include "../../types/BasicTypes.h"

namespace BOViL{
	namespace math{
		//-------------------------------------------------------------------------------------
		//------------------------- Classes ---------------------------------------------------
		//-------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		//-------------------------  Matrix related functions ---------------------------------
		//-------------------------------------------------------------------------------------
		Matrix<double> createRotationMatrixEuler(double _alpha, double _beta, double _gamma);

		//-------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		//------------------------- Spatial function ------------------------------------------
		//-------------------------------------------------------------------------------------
		Matrix<double> triangulateFromImageToGround3D(Point2ui _point2d, Matrix<double> & _camPos, Matrix<double> &_camOri, double _focalLenght, Point2d _camCentroid, double _groundAltitude = 0.0);

		//-------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
	}	// namespace geometrics

}	// namespace BOViL