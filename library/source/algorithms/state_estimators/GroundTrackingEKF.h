/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-03
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_ALGORITHMS_STATE_ESTIMATORS_GROUND_TRACKING_EKF_H_
#define _BOVIL_ALGORITHMS_STATE_ESTIMATORS_GROUND_TRACKING_EKF_H_

#include "ExtendedKalmanFilter.h"

namespace BOViL{
	namespace algorithms{
		//-----------------------------------------------------------------------------
		//----------------- Stereo Vision Class --------------------------------------
		//-----------------------------------------------------------------------------
		class GroundTrackingEKF : public ExtendedKalmanFilter{
		public:
			// In this EKF the observed state is compoud by two integers that are the pixel's X & Y of the targeting object
			// Make sure that the image has the origin (0,0) at the top on the left. If not, a transformation is necessary. 
			// Another assumtion is that the Z coordinate of the camera is upfront and the X edge has the same orientation
			// of the X edge of the image (X_c == X_img).
			
			// Set camera's parameters
			void setUpCamera(double _focalLenght, double _u0, double _v0);

			// Update camera's position and orientation. An additional parameter is the altitude of the target.
			void updateCamera(const math::Matrix<double>& _pos, const math::Matrix<double>& _ori, double _groundAltitude = 0);

		private:
			void updateJf(const double _incT);
			void updateHZk();
			void updateJh();

		private:
			double mFocalLenght;
			double mU0, mV0;

			double mGroundAltitude;

			math::Matrix<double> mPos, mOri;
		};
	}	//	namespace algorithms
}	//	namespace BOVil

#endif	//	_BOVIL_ALGORITHMS_STATE_ESTIMATORS_STEREO_VISIONEKF_H_