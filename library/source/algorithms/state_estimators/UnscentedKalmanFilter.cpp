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
			double w0 = -1;	//	666 Where is choosen?
			mSigmaPoints.push_back(pair<MatrixXd, double>(mXak, w0));



			MatrixXd lambda = n/(1-w0)*mPk;
			// Using not the square root matrix but L of cholesky decomposition
			LLT<MatrixXd> llt(lambda);
			lambda = llt.matrixL();

			for (unsigned i = 0; i < n; i++){
				double wj = (1 - w0) / 2 / n;

				mSigmaPoints.push_back(pair<MatrixXd, double>(mXak + lambda.col(i), wj));
				mSigmaPoints.push_back(pair<MatrixXd, double>(mXak - lambda.col(i), wj));
			}


		}

		//---------------------------------------------------------------------------------------------------------------------
		void UnscentedKalmanFilter::forecastStep(const double _incT){
			
			
			// Propagate sigma points through the nonlinear process model.
			vector<MatrixXd> xfkPoints;
			for(unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				 xfkPoints.push_back(systemModel(mSigmaPoints.at(i).first));
			}

			mXfk.setZero(mXfk.rows(), mXfk.cols()); // = MatrixXd::Zero(mXfk.rows(), mXfk.cols());
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

			mZk.setZero(mZk.rows(), mZk.cols()); //= MatrixXd::Zero(mZk.rows(), mZk.cols());
			for (unsigned i = 0; i < mSigmaPoints.size(); i++)	{
				mZk += zkPoints.at(i) * mSigmaPoints.at(i).second;
			}

			mCovObs = mRk;
			mCrossCov.setZero(mCrossCov.rows(), mCrossCov.cols()); // = MatrixXd::Zero(mCrossCov.rows(), mCrossCov.cols());
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
