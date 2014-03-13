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

			void getStateVector(math::Matrix<double>& _Xak) const;

		public:
			void stepEKF(const math::Matrix<double>& _Zk, const double _incT);

		private:
			void forecastStep(const double _incT);
			void filterStep(const math::Matrix<double>&_Zk);

		private:
			math::Matrix<double> mXfk, mXak, mK, mJf, mJh, mP, mQ, mR, mHZk;

		};

	}
}


#endif	// _BOVIL_ALGORITHMS_STATE_ESTIMATORS_EXTENDEDKALMANFILTER_H_