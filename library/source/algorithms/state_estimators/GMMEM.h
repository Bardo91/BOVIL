///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		EC-SAFEMOBIL: Particle Filter
//			Author: Pablo Ramon Soria
//			Date:	2015-FEB-10
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Gaussian Mixture Model - Expectation-Maximizacion algorithm.


#ifndef BOVIL_ALGORITHM_STATE_ESTIMATOR_GMMEM_H_
#define BOVIL_ALGORITHM_STATE_ESTIMATOR_GMMEM_H_

#include <array>	// 666 TODO solve.
#include <vector>

namespace BOViL {
	/** Struct that holds parameters of a gaussian distribution for a Gaussian Mixture Model (GMM)
	*/
	struct GaussianParameters{
		GaussianParameters(){};
		GaussianParameters(double _mixtureWeigh, std::array<double, 2> _mean, std::array<double, 4> _covariance) : mixtureWeigh(_mixtureWeigh), mean(_mean), covariance(_covariance) {};
		double mixtureWeigh;
		std::array<double, 2> mean;
		std::array<double, 4> covariance;
	};


	/** Class that implements a Gaussian Mixture Model Expectation-Maximization algorithm (GMMEM). 777 add reference.
	*	Particularly, classify a disjoined set of particles in 2D plane into a set of gaussians distributions.
	*/
	class GMMEM{
	public:
		/** \brief Constructor. Receive initial set of gaussians to iterate with.
		*/
		GMMEM(std::vector<std::array<double, 2>> _particles, std::vector<GaussianParameters> _gaussians);

		/** \brief Iterate. 777 need review
		*/
		bool iterate();

		/** \brief get result of iterations
		*/
		std::vector<GaussianParameters> result() const { return mGaussians; };

	private:
		std::vector<std::array<double, 2>> mParticles;
		std::vector<GaussianParameters> mGaussians;
	};
}	//	namespace BOViL.
#endif	//	BOVIL_ALGORITHM_STATE_ESTIMATOR_GMMEM_H_