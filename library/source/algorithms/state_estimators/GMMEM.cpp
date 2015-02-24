///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		EC-SAFEMOBIL: Particle Filter
//			Author: Pablo Ramon Soria
//			Date:	2015-FEB-10
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Gaussian Mixture Model - Expectation-Maximizacion algorithm.

#include "GMMEM.h"

#include <Eigen\Eigen>
#include <iostream>


using namespace std;

namespace BOViL{

	double gaussianMixtureModel(const Eigen::Vector2d& _nu, const Eigen::Matrix2d& _cov, const Eigen::Vector2d& _x);

	//---------------------------------------------------------------------------------------------------------------------
	GMMEM::GMMEM(std::vector<std::array<double, 2>> _particles,
		std::vector<GaussianParameters> _gaussians) : mParticles(_particles), mGaussians(_gaussians){ };


	//---------------------------------------------------------------------------------------------------------------------
	void GMMEM::iterate(){
		Eigen::MatrixXd membershipWeighs(mGaussians.size(), mParticles.size());
		Eigen::VectorXd N(mGaussians.size());

		if (mGaussians.size() == 0)
			return;	// No gaussians to iterate.

		unsigned steps = 0;
		double lastLikelihood = 0.0;
		double errorLikelihood = 0.0;
		do{
			double likelihood = 0.0;
			// Expectation step  ----------------
			// Calculate wik matrix dim(wik) = {n clusters, n particles}
			//		wik = gaussian(nuk, covk, xi)*alphai / (sum[m=1:k](gaussian(num, covm, xi)*alpham))
			for (unsigned pIndex = 0; pIndex < mParticles.size(); pIndex++){
				double den = 0.0;
				Eigen::Vector2d particle;
				particle << mParticles[pIndex][0], mParticles[pIndex][1];
				for (unsigned gIndex = 0; gIndex < mGaussians.size(); gIndex++){
					Eigen::Vector2d mean;
					mean << mGaussians[gIndex].mean[0], mGaussians[gIndex].mean[1];
					Eigen::Matrix2d cov;
					cov << mGaussians[gIndex].covariance[0], mGaussians[gIndex].covariance[1], mGaussians[gIndex].covariance[2], mGaussians[gIndex].covariance[3];

					den += gaussianMixtureModel(mean, cov, particle) * mGaussians[gIndex].mixtureWeigh;
				}

				for (unsigned gIndex = 0; gIndex < mGaussians.size(); gIndex++){
					Eigen::Vector2d mean;
					mean << mGaussians[gIndex].mean[0], mGaussians[gIndex].mean[1];
					Eigen::Matrix2d cov;
					cov << mGaussians[gIndex].covariance[0], mGaussians[gIndex].covariance[1], mGaussians[gIndex].covariance[2], mGaussians[gIndex].covariance[3];

					membershipWeighs(gIndex, pIndex) = gaussianMixtureModel(mean, cov, particle) *mGaussians[gIndex].mixtureWeigh / den;
				}
			}
			/*std::cout << "--------------------------------" << std::endl;
			std::cout << "Membership Weighs: " << std::endl;
			std::cout << membershipWeighs.transpose() << std::endl;*/

			// Maximization step ----------------
			// Calculate: Nk = sum[i=1:N](wik)	; N = n particles
			for (unsigned gIndex = 0; gIndex < mGaussians.size(); gIndex++){
				N[gIndex] = 0.0;
				for (unsigned pIndex = 0; pIndex < mParticles.size(); pIndex++){
					N[gIndex] += membershipWeighs(gIndex, pIndex);
				}
			}
			/*std::cout << "--------------------------------" << std::endl;
			std::cout << "N: " << std::endl;
			std::cout << N << std::endl;*/
			// Calculate mixture weighs: alpha = Nk/N
			for (unsigned i = 0; i < mGaussians.size(); i++){
				mGaussians[i].mixtureWeigh = N[i] / mParticles.size();
			}

			// Calculate: nuk = (1/Nk) * sum[i=1:N](wik*Xi)
			for (unsigned gIndex = 0; gIndex < mGaussians.size(); gIndex++){
				Eigen::Vector2d mean;
				mean << 0.0, 0.0;
				for (unsigned pIndex = 0; pIndex < mParticles.size(); pIndex++){
					Eigen::Vector2d particle;
					particle << mParticles[pIndex][0], mParticles[pIndex][1];
					mean += membershipWeighs(gIndex, pIndex)*particle;
				}
				mean /= N[gIndex];
				mGaussians[gIndex].mean[0] = mean[0];
				mGaussians[gIndex].mean[1] = mean[1];

				/*std::cout << "--------------------------------" << std::endl;
				std::cout << "mean "<< gIndex <<": " << std::endl;
				std::cout << mean << std::endl;*/
			}



			// Calculate: Covk = (1/Nk) * sum[i=1:N](wik * (xi - nuk)(xi - nuk).transpose()
			for (unsigned gIndex = 0; gIndex < mGaussians.size(); gIndex++){
				Eigen::Vector2d mean;
				mean << mGaussians[gIndex].mean[0], mGaussians[gIndex].mean[1];
				Eigen::Matrix2d cov;
				cov << 0.0, 0.0, 0.0, 0.0;
				for (unsigned pIndex = 0; pIndex < mParticles.size(); pIndex++){
					Eigen::Vector2d particle;
					particle << mParticles[pIndex][0], mParticles[pIndex][1];
					cov += membershipWeighs(gIndex, pIndex)*(particle - mean)*(particle - mean).transpose();
				}
				cov /= N[gIndex];
				mGaussians[gIndex].covariance[0] = cov(0, 0);
				mGaussians[gIndex].covariance[1] = cov(0, 1);
				mGaussians[gIndex].covariance[2] = cov(1, 0);
				mGaussians[gIndex].covariance[3] = cov(1, 1);

				/*std::cout << "--------------------------------" << std::endl;
				std::cout << "cov " << gIndex << ": " << std::endl;
				std::cout << cov << std::endl;*/
			}

			// Calc of log-likelihood
			for (unsigned pIndex = 0; pIndex < mParticles.size(); pIndex++){
				double gProb = 0.0;
				Eigen::Vector2d particle;
				particle << mParticles[pIndex][0], mParticles[pIndex][1];
				for (unsigned gIndex = 0; gIndex < mGaussians.size(); gIndex++){
					Eigen::Vector2d mean;
					mean << mGaussians[gIndex].mean[0], mGaussians[gIndex].mean[1];
					Eigen::Matrix2d cov;
					cov << mGaussians[gIndex].covariance[0], mGaussians[gIndex].covariance[1], mGaussians[gIndex].covariance[2], mGaussians[gIndex].covariance[3];
					gProb += gaussianMixtureModel(mean, cov, particle) * mGaussians[gIndex].mixtureWeigh;
				}
				likelihood += log(gProb);
			}

			errorLikelihood = abs(lastLikelihood - likelihood);
			std::cout << "lastLL: " << lastLikelihood << " - CurrentLL:" << likelihood << ". Error: " << errorLikelihood << std::endl;
			lastLikelihood = likelihood;
			steps++;
		} while (steps < 10 && errorLikelihood > 1);
	}

	//---------------------------------------------------------------------------------------------------------------------
	double gaussianMixtureModel(const Eigen::Vector2d& _nu, const Eigen::Matrix2d& _cov, const Eigen::Vector2d& _x){
		double covDet = _cov.determinant();
		/*if (covDet < 0)
			std::cout << "Estoy aqui!!" << std::endl;*/

		double res = 1 / (sqrt(pow(2 * M_PI, 2)*covDet));
		res *= exp(-0.5* (_x - _nu).transpose()*_cov.inverse()*(_x - _nu));
		return res;
	}
}	//	namespace BOViL