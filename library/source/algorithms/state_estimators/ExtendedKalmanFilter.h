/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-13
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_ALGORITHMS_STATE_ESTIMATORS_EXTENDEDKALMANFILTER_H_
#define _BOVIL_ALGORITHMS_STATE_ESTIMATORS_EXTENDEDKALMANFILTER_H_

#include <Dense>	// Eigen linear algebra library

namespace BOViL{
	namespace algorithms{
		class ExtendedKalmanFilter{
		public:
			ExtendedKalmanFilter();		// 666 TODO: initialize matrixes

			void setUpEKF(const Eigen::MatrixXd _Q, const  Eigen::MatrixXd _R, const  Eigen::MatrixXd _x0);

			Eigen::MatrixXd getStateVector() const;

		public:
			void stepEKF(const Eigen::MatrixXd& _Zk, const double _incT);

		protected:
			// Non specific funtcions of the EKF.
			virtual void updateJf(const double _incT) = 0;
			virtual void updateHZk() = 0;
			virtual void updateJh() = 0;

			// EKF steps.
			void forecastStep(const double _incT);
			void filterStep(const Eigen::MatrixXd&_Zk);

		protected:
			Eigen::MatrixXd mXfk, mXak, mK, mJf, mJh, mP, mQ, mR, mHZk;

		};	//	class ExtendedKalmanFilter

	}	//	namespace algorithms
}	//	namespace BOViL


#endif	// _BOVIL_ALGORITHMS_STATE_ESTIMATORS_EXTENDEDKALMANFILTER_H_