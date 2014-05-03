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
		void GroundTrackingEKF::updateCamera(const math::Matrix<double>& _pos, const math::Matrix<double>& _ori){
			mPos = _pos;
			mOri = _ori;
		}

		//-----------------------------------------------------------------------------
		void GroundTrackingEKF::updateJf(const double _incT){
			double arrayJf[6 * 6] = {	1, 0, 0, _incT, 0, 0,
										0, 1, 0, 0, _incT, 0,
										0, 0, 1, 0, 0, _incT,
										0, 0, 0, 1, 0, 0,
										0, 0, 0, 0, 1, 0,
										0, 0, 0, 0, 0, 1 };

			mJf = math::Matrix<double>(arrayJf, 6, 6);

		}
		//-----------------------------------------------------------------------------
		void GroundTrackingEKF::updateHZk(){
			math::Matrix<double> cPoint(mXfk.getMatrixPtr(), 3, 1);

			math::Matrix<double> Pc = mOri.transpose() * (cPoint - mPos);

			Point2d cc(mU0, mV0);

			double * hzkdata = mHZk.getMatrixPtr();

			hzkdata[0] = cc.x - mFocalLenght * Pc[1] / Pc[0];
			hzkdata[1] = cc.y - mFocalLenght * Pc[2] / Pc[0];

		}


		//-----------------------------------------------------------------------------
		void GroundTrackingEKF::updateJh(){
			math::Matrix<double> cPoint(mXfk.getMatrixPtr(), 3, 1);

			math::Matrix<double> Pc = mOri.transpose() * (cPoint - mPos);

			double * dataJh = mJh.getMatrixPtr();

			dataJh[0] = -mFocalLenght * (mOri(0, 1) * Pc[0] - mOri(0, 0) * Pc[1]) / Pc[0] / Pc[0];
			dataJh[1] = -mFocalLenght * (mOri(1, 1) * Pc[0] - mOri(1, 0) * Pc[1]) / Pc[0] / Pc[0];
			dataJh[2] = -mFocalLenght * (mOri(2, 1) * Pc[0] - mOri(2, 0) * Pc[1]) / Pc[0] / Pc[0];

			dataJh[8] = -mFocalLenght * (mOri(0, 2) * Pc[0] - mOri(0, 0) * Pc[2]) / Pc[0] / Pc[0];
			dataJh[7] = -mFocalLenght * (mOri(1, 2) * Pc[0] - mOri(1, 0) * Pc[2]) / Pc[0] / Pc[0];
			dataJh[6] = -mFocalLenght * (mOri(2, 2) * Pc[0] - mOri(2, 0) * Pc[2]) / Pc[0] / Pc[0];

			dataJh[3] = dataJh[4] = dataJh[5] = dataJh[9] = dataJh[10] = dataJh[11] = 0;

		}

	}	//	namespace algorithms
}	//	namespace BOViL