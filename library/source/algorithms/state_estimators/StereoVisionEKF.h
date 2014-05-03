/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-04-18
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_ALGORITHMS_STATE_ESTIMATORS_STEREO_VISION_EKF_H_
#define _BOVIL_ALGORITHMS_STATE_ESTIMATORS_STEREO_VISION_EKF_H_

#include "ExtendedKalmanFilter.h"

namespace BOViL{
	namespace algorithms{
		//-----------------------------------------------------------------------------
		//----------------- Stereo Vision Class --------------------------------------
		//-----------------------------------------------------------------------------
		class StereoVisionEKF: public ExtendedKalmanFilter{
		public:
			void setUpCameras(double _focalLenght, double _u0, double _v0);

			void updateCameras(	const math::Matrix<double>& _posC1, 
								const math::Matrix<double>& _posC2, 
								const math::Matrix<double>& _oriC1, 
								const math::Matrix<double>& _oriC2);

		private:
			void updateJf(const double _incT);
			void updateHZk();
			void updateJh();

		private:
			double mFocalLenght;
			double mU0, mV0;

			math::Matrix<double> mPosC1, mPosC2, mOriC1, mOriC2;
		};
	}	//	namespace algorithms
}	//	namespace BOVil

#endif	//	_BOVIL_ALGORITHMS_STATE_ESTIMATORS_STEREO_VISIONEKF_H_