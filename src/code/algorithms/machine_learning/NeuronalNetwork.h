///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _BOVIL_ALGORITHMS_MACHINELEARNING_NEURONALNETWORK_H_
#define _BOVIL_ALGORITHMS_MACHINELEARNING_NEURONALNETWORK_H_

#include <functional>
#include <vector>

namespace BOViL {
	namespace algorithms{
		/// Neuronal Network template for single or multiclass classification.
		template<unsigned InputSize_, unsigned Layers_, std::vector<unsigned> Units_, std::function<double (std::vector<double>)> Hypothesis_>
		class NeuronalNetwork{
		public:
			/// \brief Train neuronal network with the given dataset
			/// \param _x inputs of datasets.
			/// \param _y desired results for given inputs.
			bool train(std::vector<std::array<double, InputSize_>> _x, std::vector<unsigned> _y);

			/// \brief Prediction of neuronal network.
			/// \param Input values.
			unsigned evaluate(std::array<double, InputSize_> _x);

		};
	}	//	namespace algorithms
}	//	namespace BOViL

#endif _BOVIL_ALGORITHMS_MACHINELEARNING_NEURONALNETWORK_H_#pragma once
