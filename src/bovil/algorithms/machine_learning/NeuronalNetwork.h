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
			void train(const Eigen::MatrixXd &_x, const Eigen::MatrixXd &_y, double _alpha, double _lambda, unsigned _maxIter = 150, double _tol = 0.00001);
			
			/// \brief Get current parameters.
			std::array<Eigen::MatrixXd, HiddenLayers_ + 2 -1> parameters();

			/// \brief Set internalparameters of neuronal network.
			/// \param List of matrixes with layer's parameters.
			void parameters(const std::array<Eigen::MatrixXd, HiddenLayers_ + 2 -1> &_parameters);

			/// \brief Get normal values of input after training.
			std::pair<Eigen::Matrix<double, 1, InputSize_>, Eigen::Matrix<double, 1, InputSize_>> normalParams();

			/// \brief Set normal values of inputs.
			/// \param Pair with nu and sigma values of inputs.
			void normalParams(const std::pair<Eigen::Matrix<double, 1, InputSize_>, Eigen::Matrix<double, 1, InputSize_>> &normalParams);

			/// \brief get history of cost function during training
			std::vector<double> costHistory();

			/// \brief Prediction of neuronal network.
			/// \param Input values.
			Eigen::Matrix<double, OutputSize_, 1> evaluate(const Eigen::Matrix<double, InputSize_, 1> &_x);

		private:
			void randomizeParams();
			Eigen::MatrixXd appendBias(const Eigen::MatrixXd &_x);

			Eigen::MatrixXd							normalizeDataset		(const Eigen::MatrixXd &_x);
			Eigen::Matrix<double, InputSize_, 1>	normalizeInput			(const Eigen::Matrix<double, InputSize_, 1> &_x);

			Eigen::MatrixXd logarithm(const Eigen::MatrixXd &_in);
			Eigen::MatrixXd sigmoid(const Eigen::MatrixXd &_in);
			Eigen::MatrixXd sigmoidGradient(const Eigen::MatrixXd &_in);

		private:
			std::array<Eigen::MatrixXd, HiddenLayers_ + 2 - 1>	mParameters;
			std::pair<Eigen::Matrix<double, 1, InputSize_>, Eigen::Matrix<double, 1, InputSize_>>		mNormalizeParameters;	// nu and sigma of input data to normalize inputs.

			std::vector<double> mCostHistory;
		};
	}	//	namespace algorithms
}	//	namespace BOViL

#include "NeuronalNetwork.inl"

#endif //_BOVIL_ALGORITHMS_MACHINELEARNING_NEURONALNETWORK_H_