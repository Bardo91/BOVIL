///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include <iostream>

namespace BOViL {
	namespace algorithms {
		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_, unsigned HiddenLayers_, unsigned HiddenUnits_, unsigned OutputSize_>
		template<unsigned TrainSize_>
		void NeuronalNetwork<InputSize_, HiddenLayers_, HiddenUnits_, OutputSize_>::train(const Eigen::Matrix<double, TrainSize_, InputSize_> &_x, const Eigen::Matrix<double, TrainSize_, OutputSize_> &_y, double _alpha, double _lambda, unsigned _maxIter, double _tol) {
			// Init params randomlly to decouple params.
			randomizeParams();
			unsigned iters = 0;
			double lastCost = 999999;
			double cost = 0;
			do {
				std::array<Eigen::MatrixXd, HiddenLayers_ + 2 - 1> gradients;
				// Init gradients;
				gradients[0] = Eigen::MatrixXd::Zero(HiddenUnits_, InputSize_+1);
				for (unsigned i = 1; i < gradients.size(); i++) {
					gradients[i] = Eigen::Matrix<double, HiddenUnits_, HiddenUnits_+1>::Zero();
				}
				gradients[gradients.size()-1] = Eigen::MatrixXd::Zero(OutputSize_, HiddenUnits_+1);

				// For every set
				for (unsigned set = 0; set < TrainSize_; set++) {
					//  --- Feedforward propagation ---
					std::array<MatrixXd, HiddenLayers_ + 2> a;
					std::array<MatrixXd, HiddenLayers_ + 2> z;

					// Initial activation
					a[0] = _x.block<1, InputSize_>(set, 0).transpose();
					// Activations
					for (unsigned layer = 1; layer < HiddenLayers_ + 2; layer++) {
						z[layer] = mParameters[layer-1]*appendBias(a[layer-1]);
						a[layer] = sigmoid(z[layer]);
					}
					// Compute cost
					Eigen::MatrixXd h = a[a.size()-1];
					Eigen::MatrixXd y = _y.block<1, OutputSize_>(set,0).transpose();
					Eigen::MatrixXd vOnes = Eigen::MatrixXd::Ones(OutputSize_, 1);
					cost += -( y.cwiseProduct(logarithm(h))+ (vOnes - y.cwiseProduct(logarithm(vOnes - h)))).sum();

					//  --- Back propagation ---
					std::array<MatrixXd, HiddenLayers_ + 2> d;

					d[a.size()-1] = a[a.size()-1] - y;
					for (unsigned i = (HiddenLayers_ + 2 - 1) - 1; i > 0; i--) {
						d[i] = (mParameters[i].block(0, 1, mParameters[i].rows(), mParameters[i].cols()-1).transpose()*d[i+1]).cwiseProduct(sigmoidGradient(z[i]));
					}

					for (unsigned i = 0; i < HiddenLayers_ + 2 - 1; i++) {
						gradients[i] += d[i+1]*appendBias(a[i]).transpose();
					}
				}
				cost = cost/TrainSize_;
				for (unsigned i = 0; i < HiddenLayers_ + 2 - 1; i++) {
					gradients[i] /= TrainSize_;
				}

				// Regularize cost function.
				for (unsigned i = 0; i < HiddenLayers_ + 2-1; i++) {
					Eigen::MatrixXd aux = mParameters[i].block(0,1, mParameters[i].rows(), mParameters[i].cols()-1);
					cost += aux.cwiseProduct(aux).sum();
				}
				cost *= _lambda/2/TrainSize_;

				// Regularize gradient.
				for (unsigned i = 0; i < HiddenLayers_ + 2-1; i++) {
					auto aux = mParameters[i];
					aux.block(0,0,mParameters[i].rows(), 1) = Eigen::MatrixXd::Zero(mParameters[i].rows(),1);
					gradients[i] += _lambda/TrainSize_*aux;
				}

				for (unsigned i = 0; i < HiddenLayers_ + 2-1; i++) {
					mParameters[i].block(0,1, mParameters[i].rows(), mParameters[i].cols()-1) += - _alpha*gradients[i].block(0,1, gradients[i].rows(), gradients[i].cols()-1);
				}
				iters++;
			}while(iters < _maxIter/* && abs(lastCost - cos) > _tol*/);
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_, unsigned HiddenLayers_, unsigned HiddenUnits_, unsigned OutputSize_>
		Eigen::Matrix<double, OutputSize_, 1> NeuronalNetwork<InputSize_, HiddenLayers_, HiddenUnits_, OutputSize_>::evaluate(const Eigen::Matrix<double, InputSize_, 1> &_x) {
			//  --- Feedforward propagation ---
			std::array<MatrixXd, HiddenLayers_ + 2> a;
			std::array<MatrixXd, HiddenLayers_ + 2> z;
			// Initial activation
			a[0] = _x;
			// Activations
			for (unsigned layer = 1; layer < HiddenLayers_ + 2; layer++) {
				z[layer] = mParameters[layer-1]*appendBias(a[layer-1]);
				a[layer] = sigmoid(z[layer]);
			}

			return a[a.size()-1];
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_, unsigned HiddenLayers_, unsigned HiddenUnits_, unsigned OutputSize_>
		std::array<Eigen::MatrixXd, HiddenLayers_ + 2 -1> NeuronalNetwork<InputSize_, HiddenLayers_, HiddenUnits_, OutputSize_>::parameters(){
			return mParameters;
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_, unsigned HiddenLayers_, unsigned HiddenUnits_, unsigned OutputSize_>
		void NeuronalNetwork<InputSize_, HiddenLayers_, HiddenUnits_, OutputSize_>::randomizeParams() {	
			mParameters[0] = Eigen::Matrix<double, HiddenUnits_, InputSize_ + 1>::Random();
			for (unsigned i = 0; i < HiddenLayers_ - 1; i++) {
				mParameters[i+1] = Eigen::Matrix<double, HiddenUnits_, HiddenUnits_+1>::Random();
			}
			mParameters[mParameters.size()-1] = Eigen::Matrix<double, OutputSize_,HiddenUnits_ + 1> ::Random();
		}
		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_, unsigned HiddenLayers_, unsigned HiddenUnits_, unsigned OutputSize_>
		Eigen::MatrixXd NeuronalNetwork<InputSize_, HiddenLayers_, HiddenUnits_, OutputSize_>::appendBias(const Eigen::MatrixXd &_x) {
			Eigen::MatrixXd x(_x.rows() + 1, _x.cols());
			x(0, 0) = 1;
			x.block(1, 0, _x.rows(), 1) = _x;
			return x;
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_, unsigned HiddenLayers_, unsigned HiddenUnits_, unsigned OutputSize_>
		Eigen::MatrixXd NeuronalNetwork<InputSize_, HiddenLayers_, HiddenUnits_, OutputSize_>::logarithm(const Eigen::MatrixXd &_in) {
			Eigen::MatrixXd res = _in;
			for (int i = 0; i < _in.rows(); i++) {
				for (int j = 0; j < _in.cols(); j++) {
					res(i,j) = log(_in(i,j));
				}
			}
			return res;
		}
		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_, unsigned HiddenLayers_, unsigned HiddenUnits_, unsigned OutputSize_>
		Eigen::MatrixXd NeuronalNetwork<InputSize_, HiddenLayers_, HiddenUnits_, OutputSize_>::sigmoid(const Eigen::MatrixXd &_in) {
			Eigen::MatrixXd res = _in;
			for (int i = 0; i < _in.rows(); i++) {
				for (int j = 0; j < _in.cols(); j++) {
					res(i,j) = 1/(1+exp(-_in(i,j)));
				}
			}
			return res;
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_, unsigned HiddenLayers_, unsigned HiddenUnits_, unsigned OutputSize_>
		Eigen::MatrixXd NeuronalNetwork<InputSize_, HiddenLayers_, HiddenUnits_, OutputSize_>::sigmoidGradient(const Eigen::MatrixXd &_in) {
			return sigmoid(_in).cwiseProduct((MatrixXd::Ones(_in.rows(), _in.cols())-sigmoid(_in)));;
		}
	}
}