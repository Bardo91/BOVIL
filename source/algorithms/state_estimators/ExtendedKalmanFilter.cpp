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
		void ExtendedKalmanFilter::getStateVector(math::Matrix<double>& _Xak) const{
			_Xak = mXak;
		}

		//-----------------------------------------------------------------------------
		void ExtendedKalmanFilter::stepEKF(const math::Matrix<double>& _Zk, const double _incT){
			forecastStep(_incT);

			filterStep(_Zk);
		}

		//-----------------------------------------------------------------------------
		void ExtendedKalmanFilter::forecastStep(const double _incT){
			
			_incT;
			
			//updateJf(_incT);
			//
			//mXfk = mJf * mXak;
			//
			//mP = mJf * mP * mJf.t() + mQ;
		}

		//-----------------------------------------------------------------------------
		void ExtendedKalmanFilter::filterStep(const math::Matrix<double>& _Zk){
			
			_Zk;

			//updateJh_and_hZk();
			//
			//mK = mP * !mJh * ((mJh * mP * mJh.t() + mR).inv());
			//
			//mXak = mXfk + mK * (_Zk - mHZk);
			//
			//mP = (I - mK * mJh) * mP;
		}

		//-----------------------------------------------------------------------------


		//-----------------------------------------------------------------------------
	}
}