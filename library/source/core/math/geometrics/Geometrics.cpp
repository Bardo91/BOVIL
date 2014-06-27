/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Raón Soria
//		Date:	2014-05-10
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "Geometrics.h"

namespace BOViL{
	namespace math{
		//-------------------------------------------------------------------------------
		math::Matrix<double> createRotationMatrixEuler(double _alpha, double _beta, double _gamma){
			double arrayRx[9] = { 1, 0, 0,
				0, cos(_alpha), -sin(_alpha),
				0, sin(_alpha), cos(_alpha) };
			double arrayRy[9] = { cos(_beta), 0, sin(_beta),
				0, 1, 0,
				-sin(_beta), 0, cos(_beta) };
			double arrayRz[9] = { cos(_gamma), -sin(_gamma), 0,
				sin(_gamma), cos(_gamma), 0,
				0, 0, 1 };

			math::Matrix<double> Rx(arrayRx, 3, 3);
			math::Matrix<double> Ry(arrayRy, 3, 3);
			math::Matrix<double> Rz(arrayRz, 3, 3);

			return (Rx * Ry * Rz); //Euler angles.
		}


		Matrix<double> createRotationMatrix(eEdges _edge, double _angle){
			switch (_edge)
			{
			case eEdges::EdgeX:{
								   double arrayRx[9] = { 1, 0, 0,
									   0, cos(_angle), sin(_angle),
									   0, -sin(_angle), cos(_angle) };

								   return Matrix<double>(arrayRx, 3, 3);
			}
			case eEdges::EdgeY:{
								   double arrayRy[9] = { cos(_angle), 0, -sin(_angle),
									   0, 1, 0,
									   sin(_angle), 0, cos(_angle) };
								   return Matrix<double>(arrayRy, 3, 3);
			}
			case eEdges::EdgeZ:{
								   double arrayRz[9] = { cos(_angle), sin(_angle), 0,
									   -sin(_angle), cos(_angle), 0,
									   0, 0, 1 };
								   return Matrix<double>(arrayRz, 3, 3);
			}
			default:{
									double arrayR[9];
									return Matrix<double>(arrayR, 3, 3);
			}
			}

			
		}

		//-------------------------------------------------------------------------------
		Matrix<double> triangulateFromImageToGround3D(Point2ui _point2d, Matrix<double> & _camPos, Matrix<double> &_camOri, double _focalLenght, Point2d _camCentroid, double _groundAltitude){
			
			double x_c = (_groundAltitude - _camPos(2, 0)) 
											/ (	_camOri(2, 0) + 
												_camOri(2, 1)*(_camCentroid.x - _point2d.x) / _focalLenght + 
												_camOri(2, 2)*(_camCentroid.y - _point2d.y) / _focalLenght);

			double arrayP_c[3] = {	x_c,
									(_camCentroid.x - _point2d.x) / _focalLenght * x_c,
									(_camCentroid.y - _point2d.y) / _focalLenght * x_c };

			Matrix<double> Pc(arrayP_c, 3, 1);

			return _camPos + _camOri*Pc;


		}

		//-------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------

	}
}