/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-18
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "StereoVisionEKF.h"
#include "../../core/types/BasicTypes.h"


namespace BOViL {
	namespace algorithms{
		//-----------------------------------------------------------------------------
		//----------------- Stereo Vision Class --------------------------------------
		//-----------------------------------------------------------------------------
		void StereoVisionEKF::setUpCameras(double _focalLenght, double _u0, double _v0){
			mFocalLenght = _focalLenght;
			mU0 = _u0;
			mV0 = _v0;

		}

		//-----------------------------------------------------------------------------
		void StereoVisionEKF::updateCameras(	const math::Matrix<double>& _posC1, 
												const math::Matrix<double>& _posC2, 
												const math::Matrix<double>& _oriC1, 
												const math::Matrix<double>& _oriC2){
			mPosC1 = _posC1;	
			mPosC2 = _posC2;	
			mOriC1 = _oriC1;
			mOriC2 = _oriC2;
		}

		//-----------------------------------------------------------------------------
		void StereoVisionEKF::updateJf(const double _incT){
			double arrayJf[6*6] = {	1,	0,	0,	_incT,	0,		0, 
									0,	1,	0,	0,		_incT,	0, 
									0,	0,	1,	0,		0,		_incT, 
									0,	0,	0,	1,		0,		0, 
									0,	0,	0,	0,		1,		0, 
									0,	0,	0,	0,		0,		1};

			mJf = math::Matrix<double>(arrayJf, 6, 6);

		}
		//-----------------------------------------------------------------------------
		void StereoVisionEKF::updateHZk(){
			math::Matrix<double> cPoint(mXfk.getMatrixPtr(), 3, 1);
			
			math::Matrix<double> Pc1 = mOriC1.transpose() * (cPoint - mPosC1);
			math::Matrix<double> Pc2 = mOriC2.transpose() * (cPoint - mPosC2);

			mHZk(0, 0) = mU0 - mFocalLenght * Pc1(0, 0) / Pc1(2, 0);
			mHZk(1, 0) = mV0 + mFocalLenght * Pc1(1, 0) / Pc1(2, 0);
			mHZk(2, 0) = mU0 - mFocalLenght * Pc2(0, 0) / Pc2(2, 0);
			mHZk(3, 0) = mV0 + mFocalLenght * Pc2(1, 0) / Pc2(2, 0);

		}


		//-----------------------------------------------------------------------------
		void StereoVisionEKF::updateJh(){
			math::Matrix<double> cPoint(mXfk.getMatrixPtr(), 3, 1);

			math::Matrix<double> Pc1 = mOriC1.transpose() * (cPoint - mPosC1);
			math::Matrix<double> Pc2 = mOriC2.transpose() * (cPoint - mPosC2);

			double den1 = Pc1(2, 0) * Pc1(2, 0);
			double den2 = Pc2(2, 0) * Pc2(2, 0);

			mJh(0, 0) = -mFocalLenght * (mOriC1(0, 0) * Pc1(2, 0) - mOriC1(0, 2) * Pc1(0, 0)) / den1;
			mJh(0, 1) = -mFocalLenght * (mOriC1(1, 0) * Pc1(2, 0) - mOriC1(1, 2) * Pc1(0, 0)) / den1;
			mJh(0, 2) = -mFocalLenght * (mOriC1(2, 0) * Pc1(2, 0) - mOriC1(2, 2) * Pc1(0, 0)) / den1;
			   											  							  		    
			mJh(1, 0) = mFocalLenght * (mOriC1(0, 1) * Pc1(2, 0) - mOriC1(0, 2) * Pc1(1, 0)) / den1;
			mJh(1, 1) = mFocalLenght * (mOriC1(1, 1) * Pc1(2, 0) - mOriC1(1, 2) * Pc1(1, 0)) / den1;
			mJh(1, 2) = mFocalLenght * (mOriC1(2, 1) * Pc1(2, 0) - mOriC1(2, 2) * Pc1(1, 0)) / den1;  // Pc1(2,0) / Pc2(3,0);
															
			mJh(2, 0) = -mFocalLenght * (mOriC2(0, 0) * Pc2(2, 0) - mOriC2(0, 2) * Pc2(0, 0)) / den2;
			mJh(2, 1) = -mFocalLenght * (mOriC2(1, 0) * Pc2(2, 0) - mOriC2(1, 2) * Pc2(0, 0)) / den2;
			mJh(2, 2) = -mFocalLenght * (mOriC2(2, 0) * Pc2(2, 0) - mOriC2(2, 2) * Pc2(0, 0)) / den2;
														   							   		   
			mJh(3, 0) = mFocalLenght * (mOriC2(0, 1) * Pc2(2, 0) - mOriC2(0, 2) * Pc2(1, 0)) / den2;
			mJh(3, 1) = mFocalLenght * (mOriC2(1, 1) * Pc2(2, 0) - mOriC2(1, 2) * Pc2(1, 0)) / den2;
			mJh(3, 2) = mFocalLenght * (mOriC2(2, 1) * Pc2(2, 0) - mOriC2(2, 2) * Pc2(1, 0)) / den2;

			//dataJh[3] = dataJh[4] = dataJh[5] = dataJh[9] = dataJh[10] = 
			//			dataJh[11] = dataJh[15] = dataJh[16] = dataJh[17] = 
			//			dataJh[21] = dataJh[22] = dataJh[23] = 0;

		}
		
	}	//	namespace algorithms
}	//	namespace BOViL