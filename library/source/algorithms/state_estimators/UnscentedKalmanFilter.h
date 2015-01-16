/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//			Author:		Pablo Ramon Soria
//			Date:		2015-01-15
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_ALGORITHMS_STATE_ESTIMATORS_UNSCENTED_KALMAN_FILTER_H_
#define _BOVIL_ALGORITHMS_STATE_ESTIMATORS_UNSCENTED_KALMAN_FILTER_H_

#include "../../core/math/Matrix.h"

namespace BOViL{
	namespace algorithms{
		class UnscentedKalmanFilter{
		public:	// Public Interface
			UnscentedKalmanFilter();		// 666 TODO: initialize matrixes
			
			void step(const math::Matrix<double>& _Zk, const double _incT);

			math::Matrix<double> getStateVector() const;

		private:	// Private methods
			void sigmaPoints();
			void forecastStep();
			void dataStep();

		private:	// Abstract private methods
			virtual void updateJf(const double _incT) = 0;
			virtual void updateHZk() = 0;
			virtual void updateJh() = 0;

		private:	// Private members
			math::Matrix<double> Xak, Xfk, Pk;
		};
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_ALGORITHMS_STATE_ESTIMATORS_UNSCENTED_KALMAN_FILTER_H_
