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
#include <array>

namespace BOViL {
	namespace algorithms{
		/// Neuronal Network template for single or multiclass classification. Supposed hidden layers with same size.
		template<unsigned InputSize_, unsigned HiddenLayers_, unsigned HiddenUnits_, unsigned OutputSize_>
		class NeuronalNetwork{
		public:
			/// \brief Train neuronal network with the given dataset
			/// \param _x inputs of datasets.
			/// \param _y desired results for given inputs.
			template<unsigned TrainSize_>
			void train(const Eigen::Matrix<double, TrainSize_, InputSize_> &_x, const Eigen::Matrix<double, TrainSize_, OutputSize_> &_y, double _alpha, double _lambda, unsigned _maxIter = 150, double _tol = 0.00001);

			/// \brief Prediction of neuronal network.
			/// \param Input values.
			Eigen::Matrix<double, OutputSize_, 1> evaluate(const Eigen::Matrix<double, InputSize_, 1> &_x);
			
			std::array<Eigen::MatrixXd, HiddenLayers_-1+2> parameters();

		private:
			void randomizeParams();
			Eigen::MatrixXd appendBias(const Eigen::MatrixXd &_x);

			Eigen::MatrixXd logarithm(const Eigen::MatrixXd &_in);
			Eigen::MatrixXd sigmoid(const Eigen::MatrixXd &_in);
			Eigen::MatrixXd sigmoidGradient(const Eigen::MatrixXd &_in);

		private:
			std::array<Eigen::MatrixXd, HiddenLayers_ + 2 - 1> mParameters;
			/*Eigen::Matrix<double, HiddenUnits_, InputSize_ + 1> Theta1;
			Eigen::Matrix<double, OutputSize_,HiddenUnits_ + 1> ThetaN;
			std::array<Eigen::Matrix<double, HiddenUnits_, HiddenUnits_+1>, HiddenLayers_ - 1> ThetaI;*/
		};
	}	//	namespace algorithms
}	//	namespace BOViL

#include "NeuronalNetwork.inl"

#endif _BOVIL_ALGORITHMS_MACHINELEARNING_NEURONALNETWORK_H_#pragma once
