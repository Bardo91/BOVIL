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
			
			
			// Propagate sigma points through the nonlinear process model.
			vector<Matrix<double>> xfkPoints;
			for(unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				 xfkPoints.push_back(systemFunction(mSigmaPoints.at(i).first));
			}

			mXfk.empty();
			for (unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				mXfk += xfkPoints.at(i) * mSigmaPoints.at(i).second;
			}


			mPk = mQk;
			for (unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				mPk += (xfkPoints.at(i) - mXfk)*(xfkPoints.at(i) - mXfk).transpose()*mSigmaPoints.at(i).second;
			}

			//Propagate sigma points through the nonlinear observation model.
			vector<Matrix<double>> zkPoints;
			for (unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				zkPoints.push_back(observationFunction(mSigmaPoints.at(i).first));
			}

			mZk.empty();
			for (unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				mZk += zkPoints.at(i) * mSigmaPoints.at(i).second;
			}

			mCovObs = mRk;
			mCrossCov.empty();
			for (unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				mCovObs = (zkPoints.at(i) - mZk)*(zkPoints.at(i) - mZk).transpose()*mSigmaPoints.at(i).second;;
				mCrossCov = (xfkPoints.at(i) - mXfk)*(zkPoints.at(i) - mZk).transpose()*mSigmaPoints.at(i).second;;
			}

			mKk = mCrossCov*mCovObs;

		}

		//---------------------------------------------------------------------------------------------------------------------
		void UnscentedKalmanFilter::dataStep(const Matrix<double>& _Zk){
			mXak = mXfk + mKk*(_Zk - mZk);

			mPk = mPk - mKk*mCovObs*mKk.transpose();

		}

		//---------------------------------------------------------------------------------------------------------------------

	}
}
