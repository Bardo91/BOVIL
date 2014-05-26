/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-18
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "GroundTrackingEKF.h"
#include "../../core/types/BasicTypes.h"


namespace BOViL {
	namespace algorithms{
		//-----------------------------------------------------------------------------
		//----------------- Stereo Vision Class --------------------------------------
		//-----------------------------------------------------------------------------
		void GroundTrackingEKF::setUpCamera(double _focalLenght, double _u0, double _v0){
			mFocalLenght = _focalLenght;
			mU0 = _u0;
			mV0 = _v0;

		}

		//-----------------------------------------------------------------------------
		void GroundTrackingEKF::updateCamera(const math::Matrix<double>& _pos, const math::Matrix<double>& _ori, double _groundAltitude){
			mPos = _pos;
			mOri = _ori;
			mGroundAltitude = _groundAltitude;
		}

		//-----------------------------------------------------------------------------
		void GroundTrackingEKF::updateJf(const double _incT){
			double arrayJf[16] = {	1,	0,	_incT,	0,
									0,	1,	0,		_incT,
									0,	0,	1,		0,
									0,	0,	0,		1};

			mJf = math::Matrix<double>(arrayJf, 4, 4);

		}
		//-----------------------------------------------------------------------------
		void GroundTrackingEKF::updateHZk(){
			// Calculate the estimated position of the system in global coordinates
			double cPointArray[3] = { mXfk(0, 0), mXfk(1, 0), mGroundAltitude };
			math::Matrix<double> Point(cPointArray, 3, 1);

			// Point related to camera's coordinate
			math::Matrix<double> Pc = mOri.transpose() * (Point - mPos);

			// Estimation of the observation state based on actual estimation of system state ( h(·) )
			mHZk(0,0) = mU0 - mFocalLenght * Pc(0,0) / Pc(2,0);
			mHZk(1,0) = mV0 + mFocalLenght * Pc(1,0) / Pc(2,0);

		}


		//-----------------------------------------------------------------------------
		void GroundTrackingEKF::updateJh(){
			// Calculate the estimated position of the system in global coordinates
			double cPointArray[3] = { mXfk(0, 0), mXfk(1, 0), mGroundAltitude };
			math::Matrix<double> cPoint(cPointArray, 3, 1);

			// Point related to camera's coordinate
			math::Matrix<double> Pc = mOri.transpose() * (cPoint - mPos);

			// Updating the jacobian of the observation system
			mJh(0, 0) = -mFocalLenght * (mOri(0, 0) * Pc(2, 0) - mOri(0, 2) * Pc(0, 0)) / Pc(2, 0) / Pc(2, 0);
			mJh(0, 1) = -mFocalLenght * (mOri(1, 0) * Pc(2, 0) - mOri(1, 2) * Pc(0, 0)) / Pc(2, 0) / Pc(2, 0);
			//mJh(0, 2) = 0;
			//mJh(0, 3) = 0;

			mJh(1, 0) = mFocalLenght * (mOri(0, 1) * Pc(2, 0) - mOri(0, 2) * Pc(1, 0)) / Pc(2, 0) / Pc(2, 0);
			mJh(1, 1) = mFocalLenght * (mOri(1, 1) * Pc(2, 0) - mOri(1, 2) * Pc(1, 0)) / Pc(2, 0) / Pc(2, 0);
			//mJh(1, 2) = 0;
			//mJh(1, 3) = 0;

		}

	}	//	namespace algorithms
}	//	namespace BOViL