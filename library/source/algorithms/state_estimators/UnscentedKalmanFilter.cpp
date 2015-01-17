/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//			Author:		Pablo Ramon Soria
//			Date:		2015-01-16
//
/////////////////////////////////////////////////////////////////////////////////////////
//	Unscented Kalman Fiter




#include "UnscentedKalmanFilter.h"

using namespace BOViL::math;
using namespace std;

namespace BOViL{
	namespace algorithms{
		//---------------------------------------------------------------------------------------------------------------------
		UnscentedKalmanFilter::UnscentedKalmanFilter(){


		}

		//---------------------------------------------------------------------------------------------------------------------
		void UnscentedKalmanFilter::step(const math::Matrix<double>& _Zk, const double _incT) {
			sigmaPoints();
			forecastStep(_incT);
			dataStep(_Zk);
		}

		//---------------------------------------------------------------------------------------------------------------------
		Matrix<double> UnscentedKalmanFilter::state() const{
			return mXak;

		}

		//---------------------------------------------------------------------------------------------------------------------
		void UnscentedKalmanFilter::sigmaPoints(){
			unsigned n = mXak.getHeight();
			double w0 = -1;	//	666 Were is choosen?
			mSigmaPoints.push_back(pair<Matrix<double>, double>(mXak, w0));

			for (unsigned i = 0; i < n; i++){
				double wj = (1 - w0) / 2 / n;

				Matrix<double> lamda;	//666 calc lamda

				mSigmaPoints.push_back(pair<Matrix<double>, double>(mXak + lamda, wj));
				mSigmaPoints.push_back(pair<Matrix<double>, double>(mXak - lamda, wj));
			}


		}

		//---------------------------------------------------------------------------------------------------------------------
		void UnscentedKalmanFilter::forecastStep(const double _incT){

		}

		//---------------------------------------------------------------------------------------------------------------------
		void UnscentedKalmanFilter::dataStep(const math::Matrix<double>& _Zk){

		}

		//---------------------------------------------------------------------------------------------------------------------

	}
}
