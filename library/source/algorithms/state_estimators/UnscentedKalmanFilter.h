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

#include <vector>
#include <pair>

namespace BOViL{
	namespace algorithms{
		class UnscentedKalmanFilter{
		public:	// Public Interface
			UnscentedKalmanFilter();		// 666 TODO: initialize matrixes
			
			void step(const math::Matrix<double>& _Zk, const double _incT);

			math::Matrix<double> state() const;

		private:	// Private methods
			void sigmaPoints();
			void forecastStep(const double _incT);
			void dataStep(const math::Matrix<double>& _Zk);

		private:	// Abstract private methods
			virtual Matrix<double> systemModel(Matrix<double>) = 0;
			virtual Matrix<double> observerModel(Matrix<double>) = 0;

		private:	// Private members
			math::Matrix<double> mXak, mXfk, mZk, mPk, mQk, mRk, mKk;
			math::Matrix<double> mCovObs, mCrossCov;
			std::vector<pair<math::Matrix<double>,double>> mSigmaPoints;
		};
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_ALGORITHMS_STATE_ESTIMATORS_UNSCENTED_KALMAN_FILTER_H_
