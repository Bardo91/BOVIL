/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-13
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_ALGORITHMS_STATE_ESTIMATORS_EXTENDEDKALMANFILTER_H_
#define _BOVIL_ALGORITHMS_STATE_ESTIMATORS_EXTENDEDKALMANFILTER_H_

#include<Eigen/Eigen>	// Eigen linear algebra library

namespace BOViL{
	namespace algorithms{
		/** Abstrac class that implements Extended Kalman Filter (EKF) pipeline.
		*/
		class ExtendedKalmanFilter{
		public:
			/** \brief EKF class construction and initialization.
			*/
			ExtendedKalmanFilter();		// 666 TODO: initialize matrixes.

			/** \brief set EKF initial matrixes.
			*	@param _Q: 
			*	@param _R: 
			*	@param _x0: 
			*/
			void setUpEKF(const Eigen::MatrixXd _Q, const  Eigen::MatrixXd _R, const  Eigen::MatrixXd _x0);

			/** \brief get last filtered estimation. 777 rename to state().
			*/
			Eigen::MatrixXd getStateVector() const;

		public:
			/** \brief compute single step of EKF.
			*	@param _zK: observable state.
			*	@param _incT: elapsed time between previous and current state.
			*/
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