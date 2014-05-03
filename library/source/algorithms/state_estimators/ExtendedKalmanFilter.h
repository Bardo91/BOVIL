/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//		Author: Pablo Ramón Soria
//		Date:	2014-04-13
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_ALGORITHMS_STATE_ESTIMATORS_EXTENDEDKALMANFILTER_H_
#define _BOVIL_ALGORITHMS_STATE_ESTIMATORS_EXTENDEDKALMANFILTER_H_

#include "../../core/math/Matrix.h"

namespace BOViL{
	namespace algorithms{
		class ExtendedKalmanFilter{
		public:
			ExtendedKalmanFilter();		// 666 TODO: initialize matrixes

			void setUpEKF(const math::Matrix<double> _Q,const  math::Matrix<double> _R,const  math::Matrix<double> _x0);

			math::Matrix<double> getStateVector() const;

		public:
			void stepEKF(const math::Matrix<double>& _Zk, const double _incT);

		protected:
			// Non specific funtcions of the EKF.
			virtual void updateJf(const double _incT) = 0;
			virtual void updateHZk() = 0;
			virtual void updateJh() = 0;

			// EKF steps.
			void forecastStep(const double _incT);
			void filterStep(const math::Matrix<double>&_Zk);

		protected:
			math::Matrix<double> mXfk, mXak, mK, mJf, mJh, mP, mQ, mR, mHZk;

		};	//	class ExtendedKalmanFilter

	}	//	namespace algorithms
}	//	namespace BOViL


#endif	// _BOVIL_ALGORITHMS_STATE_ESTIMATORS_EXTENDEDKALMANFILTER_H_