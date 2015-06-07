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
		//----------------- Stereo Vision Class ---------------------------------------
		//-----------------------------------------------------------------------------
		/** Implementation of Extended Kalman Filter that fuse stereo camera information to estimate position
		*	of an object.
		*
		*	In this EKF the observed state is compoud by four integers that are the pixel's X & Y of the targeting object
		*	in the images. Make sure that the image has the origin (0,0) at the top on the left. If not, a transformation 
		*	is necessary. Another assumtion is that the Z coordinate of the camera is upfront and the X edge has the 
		*	same orientation of the X edge of the image (X_c == X_img).
		*/
		class StereoVisionEKF: public ExtendedKalmanFilter{
		public:
			/** \brief Set internal parameters of the camera.
			*/
			void setUpCameras(double _focalLenght, double _u0, double _v0);

			/** \brief Set position and orientation of stereo cameras.
			*/
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