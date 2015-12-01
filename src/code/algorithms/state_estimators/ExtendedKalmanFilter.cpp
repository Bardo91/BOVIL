/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-13
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ExtendedKalmanFilter.h"

#include <iostream>

using namespace Eigen;

namespace BOViL{
	namespace algorithms{
		//-----------------------------------------------------------------------------
		ExtendedKalmanFilter::ExtendedKalmanFilter(){

		}
		
		//-----------------------------------------------------------------------------
		void ExtendedKalmanFilter::setUpEKF(const MatrixXd _Q, const MatrixXd _R, const MatrixXd _x0){
			mQ = _Q;
			mR = _R;
			mXak = _x0;
			mXfk = _x0;
			mK =	MatrixXd::Zero(_Q.rows(), _R.rows());
			mJf =	MatrixXd::Identity(_Q.rows(), _Q.rows());
			mP =	MatrixXd::Identity(_Q.rows(), _Q.rows());
			mHZk =	MatrixXd::Zero(_R.rows(), 1);
			mJh =	MatrixXd::Zero(_R.rows(), _Q.rows());
		}
		
		//-----------------------------------------------------------------------------
		MatrixXd ExtendedKalmanFilter::getStateVector() const{
			return mXak;
		}

		//-----------------------------------------------------------------------------
		void ExtendedKalmanFilter::stepEKF(const MatrixXd& _Zk, const double _incT){
			forecastStep(_incT);

			filterStep(_Zk);
		}

		//-----------------------------------------------------------------------------
		void ExtendedKalmanFilter::forecastStep(const double _incT){
			updateJf(_incT);
			
			mXfk = mJf * mXak;
			
			mP = mJf * mP * mJf.transpose() + mQ;
		}

		//-----------------------------------------------------------------------------
		void ExtendedKalmanFilter::filterStep(const MatrixXd& _Zk){
			updateHZk();
			updateJh();

			mK = mP * mJh.transpose() * ((mJh * mP * mJh.transpose() + mR).inverse());
			
			mXak = mXfk + mK * (_Zk - mHZk);
			
			MatrixXd I = MatrixXd::Identity(mK.rows(), mK.rows());

			mP = (I - mK * mJh) * mP;
		}

		//-----------------------------------------------------------------------------


		//-----------------------------------------------------------------------------
	}
}