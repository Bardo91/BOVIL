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
using namespace Eigen;

namespace BOViL{
	namespace algorithms{
		//---------------------------------------------------------------------------------------------------------------------
		UnscentedKalmanFilter::UnscentedKalmanFilter(){


		}

		//---------------------------------------------------------------------------------------------------------------------
		void UnscentedKalmanFilter::step(const MatrixXd& _Zk, const double _incT) {
			sigmaPoints();
			forecastStep(_incT);
			dataStep(_Zk);
		}

		//---------------------------------------------------------------------------------------------------------------------
		MatrixXd UnscentedKalmanFilter::state() const{
			return mXak;

		}

		//---------------------------------------------------------------------------------------------------------------------
		void UnscentedKalmanFilter::sigmaPoints(){
			unsigned n = mXak.rows();
			double w0 = -1;	//	666 Were is choosen?
			mSigmaPoints.push_back(pair<MatrixXd, double>(mXak, w0));

			for (unsigned i = 0; i < n; i++){
				double wj = (1 - w0) / 2 / n;

				MatrixXd lamda;	//666 calc lamda (square root matrix)

				mSigmaPoints.push_back(pair<MatrixXd, double>(mXak + lamda, wj));
				mSigmaPoints.push_back(pair<MatrixXd, double>(mXak - lamda, wj));
			}


		}

		//---------------------------------------------------------------------------------------------------------------------
		void UnscentedKalmanFilter::forecastStep(const double _incT){
			
			
			// Propagate sigma points through the nonlinear process model.
			vector<MatrixXd> xfkPoints;
			for(unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				 xfkPoints.push_back(systemModel(mSigmaPoints.at(i).first));
			}

			mXfk = MatrixXd::Zero(mXfk.rows(), mXfk.cols());
			for (unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				mXfk += xfkPoints.at(i) * mSigmaPoints.at(i).second;
			}


			mPk = mQk;
			for (unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				mPk += (xfkPoints.at(i) - mXfk)*(xfkPoints.at(i) - mXfk).transpose()*mSigmaPoints.at(i).second;
			}

			//Propagate sigma points through the nonlinear observation model.
			vector<MatrixXd> zkPoints;
			for (unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				zkPoints.push_back(observerModel(mSigmaPoints.at(i).first));
			}

			mZk = MatrixXd::Zero(mZk.rows(), mZk.cols());
			for (unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				mZk += zkPoints.at(i) * mSigmaPoints.at(i).second;
			}

			mCovObs = mRk;
			mCrossCov = MatrixXd::Zero(mCrossCov.rows(), mCrossCov.cols());
			for (unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				mCovObs = (zkPoints.at(i) - mZk)*(zkPoints.at(i) - mZk).transpose()*mSigmaPoints.at(i).second;;
				mCrossCov = (xfkPoints.at(i) - mXfk)*(zkPoints.at(i) - mZk).transpose()*mSigmaPoints.at(i).second;;
			}

			mKk = mCrossCov*mCovObs;

		}

		//---------------------------------------------------------------------------------------------------------------------
		void UnscentedKalmanFilter::dataStep(const MatrixXd& _Zk){
			mXak = mXfk + mKk*(_Zk - mZk);

			mPk = mPk - mKk*mCovObs*mKk.transpose();

		}

		//---------------------------------------------------------------------------------------------------------------------

	}
}
