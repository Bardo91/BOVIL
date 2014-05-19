/////////////////////////////////////////////////////////////////////////////////////////
//	EC-SAFEMOBIL: Ground Station - Tracking Ground Objects
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-19
//
/////////////////////////////////////////////////////////////////////////////////////////


#include "MathGeometrics.h"

//---------------------------------------------------------------------------------------
double minDist2Lines(BOViL::math::Matrix<double> _c1,
	BOViL::math::Matrix<double> _c2,
	BOViL::math::Matrix<double> _r1,
	BOViL::math::Matrix<double> _r2,
	BOViL::Point2ui _p1,
	BOViL::Point2ui _p2,
	double _focalLenght){

	// Direction of lines in camera's coordinates.
	double arrayU1_c[3] = { 1, _p1.x / _focalLenght, _p1.y / _focalLenght };
	BOViL::math::Matrix<double> u1_c(arrayU1_c, 3, 1);
	double arrayU2_c[3] = { 1, _p2.x / _focalLenght, _p2.y / _focalLenght };
	BOViL::math::Matrix<double> u2_c(arrayU2_c, 3, 1);

	// Direction of lines in world coordiantes.
	BOViL::math::Matrix<double> u1 = _r1*u1_c;
	BOViL::math::Matrix<double> u2 = _r2*u2_c;

	double u1u1 = (u1.transpose() * u1)(0, 0);
	double u1u2 = (u1.transpose() * u2)(0, 0);// == u2u1
	double u2u2 = (u2.transpose() * u2)(0, 0);

	// Diference of origins
	BOViL::math::Matrix<double> c2c1 = _c2 - _c1;

	// Parameters that minimices the distance
	//------------------------------------------------
	//-----  P1P2 = [C2-C1] + u2*alpha - u1*beta -----
	//------------------------------------------------
	double beta = (((c2c1.transpose() * u1) * (u2u2 / u1u2) - c2c1.transpose() * u2)(0, 0))
		/ (u1u1 * u2u2 / u1u2 - u1u2);

	double alpha = (u1u1 * beta - (c2c1.transpose() * u1)(0, 0))
		/ u1u2;

	BOViL::math::Matrix<double> P1P2 = _c2 - _c1 + u2*alpha - u1*beta;

	return P1P2.norm();

}

//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------