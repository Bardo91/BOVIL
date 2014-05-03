/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-03
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_ALGORITHMS_STATE_ESTIMATORS_POSITION_ESTIMATOR_N_CAMERAS_H_
#define _BOVIL_ALGORITHMS_STATE_ESTIMATORS_POSITION_ESTIMATOR_N_CAMERAS_H_

#include "ExtendedKalmanFilter.h"

namespace BOViL	{
	namespace algorithms	{
		class PositionEstimatorNCamerasEKF: public ExtendedKalmanFilter	{
		public:		// Member functions of soon


		public:		// Overridable members
			void updateJf(const double _incT);
			void updateHZk();
			void updateJh();

		private:	//	private members
			int mNoCams = 0;

			// 666 TODO: camera's info storage

		};	// class PositionEstimatorNCamerasEKF
	}
}	//	namespace BOViL



#endif		//	_BOVIL_ALGORITHMS_STATE_ESTIMATORS_POSITION_ESTIMATOR_N_CAMERAS_H_