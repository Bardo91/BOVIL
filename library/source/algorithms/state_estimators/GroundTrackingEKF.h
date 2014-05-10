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
			void setUpCamera(double _focalLenght, double _u0, double _v0);

			void updateCamera(const math::Matrix<double>& _pos, const math::Matrix<double>& _ori, double _groundAltitude);

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