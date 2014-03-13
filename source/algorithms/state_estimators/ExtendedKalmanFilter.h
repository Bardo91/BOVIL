/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: filters
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-13
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_ALGORITHMS_STATE_ESTIMATORS_EXTENDEDKALMANFILTER_H_
#define _BOVIL_ALGORITHMS_STATE_ESTIMATORS_EXTENDEDKALMANFILTER_H_

#include "../../core/math/Matrix.h"

namespace BOViL{
	namespace state_estimators{
		class ExtendedKalmanFilter{
		public:
			ExtendedKalmanFilter();

		private:
			void forecastStep();
			void filterStep(math::Matrix<double>&_Zk);

		public:
			void stepEKF(math::Matrix<double>& _Zk, double _incT);

			math::Matrix<double> getStateVector() const;

		private:
			math::Matrix<double> Xfk, Xak, K, Jf, Jh, P, Q, R, h_Zk;
			double incT;
		};

	}
}


#endif	// _BOVIL_ALGORITHMS_STATE_ESTIMATORS_EXTENDEDKALMANFILTER_H_