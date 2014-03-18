/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: filters
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-13
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
			mP = math::createEye<double>(_Q.getHeight());
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
			
			mP = mJf * mP * !mJf + mQ;
		}

		//-----------------------------------------------------------------------------
		void ExtendedKalmanFilter::filterStep(const math::Matrix<double>& _Zk){
			updateHZk();
			updateJh();
			
			mK = mP * !mJh * ((mJh * mP * !mJh + mR)^-1);
			
			mXak = mXfk + mK * (_Zk - mHZk);
			
			mP = (math::createEye<double>(mK.getHeight()) - mK * mJh) * mP;
		}

		//-----------------------------------------------------------------------------


		//-----------------------------------------------------------------------------
	}
}