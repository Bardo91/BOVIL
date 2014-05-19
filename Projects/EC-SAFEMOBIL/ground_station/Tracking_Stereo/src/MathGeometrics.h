/////////////////////////////////////////////////////////////////////////////////////////
//	EC-SAFEMOBIL: Ground Station - Tracking Ground Objects
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-19
//
/////////////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------------------
#ifndef _ECSAFEMOBIL_TRACKING_STEREO
#define _ECSAFEMOBIL_TRACKING_STEREO

// INCLUDES
#include <core/math/Matrix.h>
#include <core/types/BasicTypes.h>


// FUNCTIONS
//---------------------------------------------------------------------------------------
double minDist2Lines(	BOViL::math::Matrix<double> _c1,
						BOViL::math::Matrix<double> _c2,
						BOViL::math::Matrix<double> _r1,
						BOViL::math::Matrix<double> _r2,
						BOViL::Point2d _p1,
						BOViL::Point2d _p2,
						double _focalLenght);

//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------


#endif _ECSAFEMOBIL_TRACKING_STEREO