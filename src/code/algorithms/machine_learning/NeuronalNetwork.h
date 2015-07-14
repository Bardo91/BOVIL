///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _BOVIL_ALGORITHMS_MACHINELEARNING_NEURONALNETWORK_H_
#define _BOVIL_ALGORITHMS_MACHINELEARNING_NEURONALNETWORK_H_

#include <Eigen/Eigen>
#include <functional>
#include <vector>

namespace BOViL {
	namespace algorithms{
		/// Neuronal Network template for single or multiclass classification. Supposed hidden layers with same size.
		template<unsigned InputSize_, unsigned Layers_, unsigned HiddenUnits_, unsigned OutputSize_>
		class NeuronalNetwork{
		public:
			/// \brief Train neuronal network with the given dataset
			/// \param _x inputs of datasets.
			/// \param _y desired results for given inputs.
			template<unsigned TrainSize_>
			void train(const Eigen::Matrix<double, TrainSize_, InputSize_> &_x, const Eigen::Matrix<double, TrainSize_, OutputSize_> &_y);

			/// \brief Prediction of neuronal network.
			/// \param Input values.
			Eigen::Matrix<double, OutputSize_, 1> evaluate(const Eigen::Matrix<double, InputSize_, 1> &_x);
			
		};
	}	//	namespace algorithms
}	//	namespace BOViL

#include "NeuronalNetwork.inl"

#endif _BOVIL_ALGORITHMS_MACHINELEARNING_NEURONALNETWORK_H_#pragma once
