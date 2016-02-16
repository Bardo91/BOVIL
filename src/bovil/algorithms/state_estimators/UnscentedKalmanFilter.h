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
#include <Eigen/Eigen>

namespace BOViL{
	namespace algorithms{
		/** Abstrac class that implements Unescented Kalman Filter (UKF) pipeline.
		*/
		class UnscentedKalmanFilter{
		public:	// Public Interface
			/** \brief EKF class construction and initialization.
			*/
			UnscentedKalmanFilter();		// 666 TODO: initialize matrixes
			
			/** \brief compute single step of UKF.
			*	@param _zK: observable state.
			*	@param _incT: elapsed time between previous and current state.
			*/
			void step(const Eigen::MatrixXd& _Zk, const double _incT);

			/** \brief get last filtered estimation.
			*/
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
