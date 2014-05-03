/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-13
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ExtendedKalmanFilter.h"


namespace BOViL{
	namespace algorithms{
		//-----------------------------------------------------------------------------
		ExtendedKalmanFilter::ExtendedKalmanFilter(){

		}
		
		//-----------------------------------------------------------------------------
		void ExtendedKalmanFilter::setUpEKF(const math::Matrix<double> _Q, const math::Matrix<double> _R, const math::Matrix<double> _x0){
			mQ = _Q;
			mR = _R;
			mXak = _x0;
			mXfk = _x0;
			mK = math::createEye<double>(_Q.getHeight());;
			mJf = math::createEye<double>(_Q.getHeight());;
			mP = math::createEye<double>(_Q.getHeight());
			mHZk = math::Matrix<double>(_Q.getHeight(), 1);
			mJh = math::Matrix<double>(_R.getHeight(), _Q.getHeight());
		}
		
		//-----------------------------------------------------------------------------
		math::Matrix<double> ExtendedKalmanFilter::getStateVector() const{
			return mXak;
		}

		//-----------------------------------------------------------------------------
		void ExtendedKalmanFilter::stepEKF(const math::Matrix<double>& _Zk, const double _incT){
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
		void ExtendedKalmanFilter::filterStep(const math::Matrix<double>& _Zk){
			updateHZk();
			updateJh();

			math::Matrix<double> auxT(mJh.transpose());
			mK = mP * auxT * ((mJh * mP * auxT + mR) ^ -1);
			
			mXak = mXfk + mK * (_Zk - mHZk);
			
			mP = (math::createEye<double>(mK.getHeight()) - mK * mJh) * mP;
		}

		//-----------------------------------------------------------------------------


		//-----------------------------------------------------------------------------
	}
}