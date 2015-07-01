///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _BOVIL_ALGORITHMS_MACHINELEARNING_REGRESSION_H_
#define _BOVIL_ALGORITHMS_MACHINELEARNING_REGRESSION_H_

#include <array>
#include <functional>
#include <vector>

namespace BOViL {
	namespace algorithms{
		/// Base tamplate of Regression algorithms (i.e. LinealRegression, PolinomialRegression, Logistic Regression, 
		/// etc.).
		template<unsigned InputSize_, std::vector<unsigned> Polinom_, std::function<double (std::vector<double>)> Hypothesis_>
		class Regression{
		public:
			/// \brief Traing network with given dataset.
			/// \param _x inputs of datasets.
			/// \param _y desired results for given inputs.
			bool train(std::vector<std::array<double, InputSize_>> _x, std::vector<double> _y);

			/// \brief Prediction of Regression.
			/// \param Input values.
			double evaluate(std::array<double, InputSize_> _x);

		};
	}	//	namespace algorithms
}	//	namespace BOViL

#endif _BOVIL_ALGORITHMS_MACHINELEARNING_REGRESSION_H_