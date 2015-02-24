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
	struct GaussianParameters{
		GaussianParameters(){};
		GaussianParameters(double _mixtureWeigh, std::array<double, 2> _mean, std::array<double, 4> _covariance) : mixtureWeigh(_mixtureWeigh), mean(_mean), covariance(_covariance) {};
		double mixtureWeigh;
		std::array<double, 2> mean;
		std::array<double, 4> covariance;
	};

	class GMMEM{
	public:
		GMMEM(std::vector<std::array<double, 2>> _particles, std::vector<GaussianParameters> _gaussians);

		void iterate();

		std::vector<GaussianParameters> result() const { return mGaussians; };

	private:
		std::vector<std::array<double, 2>> mParticles;
		std::vector<GaussianParameters> mGaussians;
	};
}	//	namespace BOViL.
#endif	//	BOVIL_ALGORITHM_STATE_ESTIMATOR_GMMEM_H_