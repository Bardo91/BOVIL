/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: filters
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-13
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ExtendedKalmanFilter.h"


namespace BOViL{
	namespace state_estimators{
		//-----------------------------------------------------------------------------
		ExtendedKalmanFilter::ExtendedKalmanFilter(){

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