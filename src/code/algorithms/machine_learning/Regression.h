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
		template<unsigned Nvars_, unsigned Nmonomials_>
		class Regression{
		public:	// Public interface
			/// Build a regression with the given hypothesys.
			/// \param _hypothesis Polinomial equation that defines the hypothesis
			Regression(const Polynomial<Nvars_, Nmonomials_> &_hypothesis);

			/// \brief Traing network with given dataset.
			/// \tparam TrainSize_ size of training set
			/// \param _x inputs of datasets.
			/// \param _y desired results for given inputs.
			/// \param _alpha gradient coefficient
			/// \param _lambda regularization parameter
			/// \param _maxIter maximum number of iteration allowed
			template <unsigned TrainSize_>
			void train(const Eigen::Matrix<double, TrainSize_, Nmonomials_> &_x, const Eigen::Matrix<double, TrainSize_, 1> &_y, double _alpha, double _lambda, unsigned _maxIter = 150, double _tol = 0.00001);

			/// \brief Prediction of Regression.
			/// \param Input values.
			double evaluate(const Eigen::Matrix<double, 1, Nvars_> &_x) const;

			Polynomial<Nvars_, Nmonomials_> hypothesis() const;
		private:
			Eigen::Matrix<double, Nmonomials_,1> gradient(const Eigen::Matrix<double, 1, Nmonomials_> &_x, double _y) const;

			// For debugging purposes.
			double cost(const Eigen::Matrix<double, 1, Nmonomials_> &_x, double _y) const;

		private:	// Private members
			Polynomial<Nvars_, Nmonomials_>	mHypothesis;

		};
	}	//	namespace algorithms
}	//	namespace BOViL

#include "Regression.inl"

#endif _BOVIL_ALGORITHMS_MACHINELEARNING_REGRESSION_H_