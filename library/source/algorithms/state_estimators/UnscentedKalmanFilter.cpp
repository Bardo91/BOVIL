/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: algorithms
//
//			Author:		Pablo Ramon Soria
//			Date:		2015-01-16
//
/////////////////////////////////////////////////////////////////////////////////////////
//	Unscented Kalman Fiter




#include "UnscentedKalmanFilter.h"

#include <vector>

using namespace std;
using namespace BOViL::math;

namespace BOViL{
	namespace algorithms{
		//---------------------------------------------------------------------------------------------------------------------
		UnscentedKalmanFilter::UnscentedKalmanFilter(){


		}

		//---------------------------------------------------------------------------------------------------------------------
		void UnscentedKalmanFilter::step(const Matrix<double>& _Zk, const double _incT) {
			sigmaPoints();
			forecastStep(_incT);
			dataStep(_Zk);
		}

		//---------------------------------------------------------------------------------------------------------------------
		math::Matrix<double> UnscentedKalmanFilter::state() const{
			return mXak;

		}

		//---------------------------------------------------------------------------------------------------------------------
		void UnscentedKalmanFilter::sigmaPoints(){

		}

		//---------------------------------------------------------------------------------------------------------------------
		void UnscentedKalmanFilter::forecastStep(const double _incT){
			
			
			vector<Matrix<double>> xfkPoints;

			for(unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				 xfkPoints.push_back(systemFunction(mSigmaPoints.at(i).first));
			}

			mXfk.empty();
			for (unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				mXfk += mSigmaPoints.at(i).first * mSigmaPoints.at(i).second;
			}

		}

		//---------------------------------------------------------------------------------------------------------------------
		void UnscentedKalmanFilter::dataStep(const Matrix<double>& _Zk){

		}

		//---------------------------------------------------------------------------------------------------------------------

	}
}
