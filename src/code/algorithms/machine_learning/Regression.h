////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _BOVIL_ALGORITHMS_MACHINELEARNING_REGRESSION_H_
#define _BOVIL_ALGORITHMS_MACHINELEARNING_REGRESSION_H_

#include <array>
#include <Eigen/Eigen>
#include <vector>

#include "Polynomial.h"

namespace BOViL {
	namespace algorithms{
		/// Base tamplate of Regression algorithms (i.e. LinealRegression, PolinomialRegression, Logistic Regression, 
		/// etc.). Now cost function is always square function. Regression takes as template arguments:
		/// \tparam InputSize_ number of variables + 1. (ex. a0 + a1*x1 + a2*x2 --> InputSize_ = 3)
		template<unsigned Nvar_, unsigned Nmonomials_>
		class Regression{
		public:	// Public interface
			/// Redefinition for easy usage.
			typedef Polynomial<Nvar_, Nmonomials_> Hypothesyis;

			/// Build a regression with the given hypothesys.
			Regression(const Hypothesyis &_hypothesis);

			/// \brief Traing network with given dataset.
			/// \tparam TrainSize_ size of training set
			/// \param _x inputs of datasets.
			/// \param _y desired results for given inputs.
			template <unsigned TrainSize_>
			bool train(const Eigen::Matrix<double, TrainSize_, Nmonomials_> &_x, const Eigen::Matrix<double, TrainSize_, 1> &_y, double _alpha, unsigned _maxIter = 150);

			/// \brief Prediction of Regression.
			/// \param Input values.
			double evaluate(const Hypothesyis::Input &_x);

		private:
			Eigen::Matrix<double, Nmonomials_, 1> gradient();

		private:	// Private members
			Hypothesyis	mHypothesys;

		};
	}	//	namespace algorithms
}	//	namespace BOViL

#include "Regression.inl"

#endif _BOVIL_ALGORITHMS_MACHINELEARNING_REGRESSION_H_