/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: filters
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-18
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
		void StereoVisionEKF::updateCameras(	const math::Matrix<double> _posC1, 
												const math::Matrix<double> _posC2, 
												const math::Matrix<double> _oriC1, 
												const math::Matrix<double> _oriC2){
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

			math::Matrix<double> Pc1 = !mOriC1 * (cPoint - mPosC1);
			math::Matrix<double> Pc2 = !mOriC2 * (cPoint - mPosC2);

			double* pc1data = Pc1.getMatrixPtr();
			double* pc2data = Pc2.getMatrixPtr();

			double PXc1 = pc1data[0];
			double PYc1 = pc1data[1];
			double PZc1 = pc1data[2];
			double PXc2 = pc2data[0];
			double PYc2 = pc2data[1];
			double PZc2 = pc2data[2];

			Point2d cc1(mU0, mV0);
			Point2d cc2(mU0, mV0);

			double * hzkdata = mHZk.getMatrixPtr();

			hzkdata[0] = cc1.x - mFocalLenght * PYc1 / PXc1;
			hzkdata[1] = cc1.y - mFocalLenght * PZc1 / PXc1;
			hzkdata[2] = cc2.x - mFocalLenght * PYc2 / PXc2;
			hzkdata[3] = cc2.y - mFocalLenght * PZc2 / PXc2;

		}


		//-----------------------------------------------------------------------------
		void StereoVisionEKF::updateJh(){
			double * R1 = mOriC1.getMatrixPtr();
			double * R2 = mOriC2.getMatrixPtr();
			
			math::Matrix<double> cPoint(mXfk.getMatrixPtr(), 3, 1);

			math::Matrix<double> Pc1 = !mOriC1 * (cPoint - mPosC1);
			math::Matrix<double> Pc2 = !mOriC2 * (cPoint - mPosC2);

			double* pc1data = Pc1.getMatrixPtr();
			double* pc2data = Pc2.getMatrixPtr();

			double PXc1 = pc1data[0];
			double PYc1 = pc1data[1];
			double PZc1 = pc1data[2];
			double PXc2 = pc2data[0];
			double PYc2 = pc2data[1];
			double PZc2 = pc2data[2];

			double * dataJh = mJh.getMatrixPtr();


			dataJh[0] = -mFocalLenght * (R1[3 * 0 + 1] * PXc1 - R1[3 * 0 + 0] * PYc1) / PXc1 / PXc1;
			dataJh[1] = -mFocalLenght * (R1[3 * 1 + 1] * PXc1 - R1[3 * 1 + 0] * PYc1) / PXc1 / PXc1;
			dataJh[2] = -mFocalLenght * (R1[3 * 2 + 1] * PXc1 - R1[3 * 2 + 0] * PYc1) / PXc1 / PXc1;
						 
			dataJh[8] = -mFocalLenght * (R1[3 * 0 + 2] * PXc1 - R1[3 * 0 + 0] * PZc1) / PXc1 / PXc1;
			dataJh[7] = -mFocalLenght * (R1[3 * 1 + 2] * PXc1 - R1[3 * 1 + 0] * PZc1) / PXc1 / PXc1;
			dataJh[6] = -mFocalLenght * (R1[3 * 2 + 2] * PXc1 - R1[3 * 2 + 0] * PZc1) / PXc1 / PXc1;

			dataJh[12] = -mFocalLenght * (R2[3 * 0 + 1] * PXc2 - R2[3 * 0 + 0] * PYc2) / PXc2 / PXc2;
			dataJh[13] = -mFocalLenght * (R2[3 * 1 + 1] * PXc2 - R2[3 * 1 + 0] * PYc2) / PXc2 / PXc2;
			dataJh[14] = -mFocalLenght * (R2[3 * 2 + 1] * PXc2 - R2[3 * 2 + 0] * PYc2) / PXc2 / PXc2;
						  
			dataJh[18] = -mFocalLenght * (R2[3 * 0 + 2] * PXc2 - R2[3 * 0 + 0] * PZc2) / PXc2 / PXc2;
			dataJh[19] = -mFocalLenght * (R2[3 * 1 + 2] * PXc2 - R2[3 * 1 + 0] * PZc2) / PXc2 / PXc2;
			dataJh[20] = -mFocalLenght * (R2[3 * 2 + 2] * PXc2 - R2[3 * 2 + 0] * PZc2) / PXc2 / PXc2;	

			dataJh[3] = dataJh[4] = dataJh[5] = dataJh[9] = dataJh[10] = 
						dataJh[11] = dataJh[15] = dataJh[16] = dataJh[17] = 
						dataJh[21] = dataJh[22] = dataJh[23] = 0;

		}
		
		//-----------------------------------------------------------------------------
		math::Matrix<double> createRotationMatrixEuler(double _alpha, double _beta, double _gamma){
			double arrayRx[9] = {	1,			0,					0, 
									0,			cos(_alpha),		-sin(_alpha), 
									0,			sin(_alpha),		cos(_alpha)};
			double arrayRy[9] = {	cos(_beta),		0,			sin(_beta), 
									0,				1,			0, 
									-sin(_beta),	0,			cos(_beta)};
			double arrayRz[9] = {	cos(_gamma),	-sin(_gamma),	0, 
									sin(_gamma),	cos(_gamma),	0, 
									0,				0,				1};
			
			math::Matrix<double> Rx(arrayRx , 3, 3);

			math::Matrix<double> Ry(arrayRy, 3, 3);

			math::Matrix<double> Rz(arrayRz, 3, 3);

			return (Rx * Ry * Rz); //Euler angles.

		}
	}	//	namespace algorithms
}	//	namespace BOViL