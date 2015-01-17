/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//		Author: Pablo Ramón Soria
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

			void updateCameras(	const Eigen::Matrix<double, 3, 1>& _posC1, 
								const Eigen::Matrix<double, 3, 1>& _posC2, 
								const Eigen::Matrix<double, 3, 3>& _oriC1, 
								const Eigen::Matrix<double, 3, 3>& _oriC2);

		private:
			void updateJf(const double _incT);
			void updateHZk();
			void updateJh();

		private:
			double mFocalLenght;
			double mU0, mV0;

			Eigen::Matrix<double, 3, 1> mPosC1, mPosC2;
			Eigen::Matrix<double, 3, 3> mOriC1, mOriC2;
		};
	}	//	namespace algorithms
}	//	namespace BOVil

#endif	//	_BOVIL_ALGORITHMS_STATE_ESTIMATORS_STEREO_VISIONEKF_H_