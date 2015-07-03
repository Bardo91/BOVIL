///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _BOVIL_ALGORITHMS_MACHINELEARNING_REGRESSION_H_
#define _BOVIL_ALGORITHMS_MACHINELEARNING_REGRESSION_H_

#include <array>
#include <Eigen/Eigen>
#include <functional>
#include <vector>

namespace BOViL {
	namespace algorithms{
		/// Base tamplate of Regression algorithms (i.e. LinealRegression, PolinomialRegression, Logistic Regression, 
		/// etc.). Regression takes as template arguments
		/// \tparam InputSize_ number of parameters
		/// \tparam Polinom_ superior triangular matrix that defines the hypothesys.
		template<unsigned InputSize_>
		class Regression{
		public:
			/// Build a regression with the given hypothesys.
			Regression(const Eigen::Matrix<double, InputSize_, InputSize_> &_hypothesis);

			/// \brief Traing network with given dataset.
			/// \tparam TrainSize_ size of training set
			/// \param _x inputs of datasets.
			/// \param _y desired results for given inputs.
			template <unsigned TrainSize_>
			bool train(const Eigen::Matrix<double, TrainSize_, InputSize_> &_x, const Eigen::Matrix<double, TrainSize_, 1> &_y);

			/// \brief Prediction of Regression.
			/// \param Input values.
			double evaluate(const Eigen::Matrix<double, InputSize_, 1> &_x);

		};
	}	//	namespace algorithms
}	//	namespace BOViL

#include "Regression.inl"

#endif _BOVIL_ALGORITHMS_MACHINELEARNING_REGRESSION_H_