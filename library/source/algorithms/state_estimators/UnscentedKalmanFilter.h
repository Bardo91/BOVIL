/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//			Author:		Pablo Ramon Soria
//			Date:		2015-01-15
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_ALGORITHMS_STATE_ESTIMATORS_UNSCENTED_KALMAN_FILTER_H_
#define _BOVIL_ALGORITHMS_STATE_ESTIMATORS_UNSCENTED_KALMAN_FILTER_H_

#include <vector>
#include <Dense>

namespace BOViL{
	namespace algorithms{
		class UnscentedKalmanFilter{
		public:	// Public Interface
			UnscentedKalmanFilter();		// 666 TODO: initialize matrixes
			
			void step(const Eigen::MatrixXd& _Zk, const double _incT);

			Eigen::MatrixXd state() const;

		private:	// Private methods
			void sigmaPoints();
			void forecastStep(const double _incT);
			void dataStep(const Eigen::MatrixXd& _Zk);

		private:	// Abstract private methods
			virtual Eigen::MatrixXd systemModel(Eigen::MatrixXd) = 0;
			virtual Eigen::MatrixXd observerModel(Eigen::MatrixXd) = 0;

		private:	// Private members
			Eigen::MatrixXd mXak, mXfk, mZk, mPk, mQk, mRk, mKk;
			Eigen::MatrixXd mCovObs, mCrossCov;
			std::vector<std::pair<Eigen::MatrixXd, double>> mSigmaPoints;
		};
	}	//	namespace comm
}	//	namespace BOViL

#endif	// _BOVIL_ALGORITHMS_STATE_ESTIMATORS_UNSCENTED_KALMAN_FILTER_H_
