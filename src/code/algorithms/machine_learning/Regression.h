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
		/// etc.).
		template<unsigned InputSize_, Eigen::Matrix<double, InputSize_, InputSize_> Polinom_, std::function<double (std::vector<double>)> Hypothesis_>
		class Regression{
		public:
			/// \brief Traing network with given dataset.
			/// \param _x inputs of datasets.
			/// \param _y desired results for given inputs.
			template <unsigned TrainSize_>
			bool train(Eigen::Matrix<double, TrainSize_, InputSize_> _x, Eigen::Matrix<double, TrainSize_, 1> _y);

			/// \brief Prediction of Regression.
			/// \param Input values.
			double evaluate(Eigen::Matrix<double, InputSize_, 1> _x);

		};
	}	//	namespace algorithms
}	//	namespace BOViL

#include "Regression.inl"

#endif _BOVIL_ALGORITHMS_MACHINELEARNING_REGRESSION_H_