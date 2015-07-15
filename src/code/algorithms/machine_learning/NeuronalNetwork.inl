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
			const int cNuLayers = HiddenLayers_ + 2;
			// Init params randomlly to decouple params.
			randomizeParams();
			std::cout << mParameters[0] << std::endl << std::endl;
			std::cout << mParameters[1] << std::endl << std::endl;
			unsigned iters = 0;
			double lastCost = 999999;
			double cost = 0;
			do {
				std::array<Eigen::MatrixXd, cNuLayers - 1> gradients;
				gradients[0] = Eigen::MatrixXd::Zero(HiddenUnits_, InputSize_+1);
				gradients[1] = Eigen::MatrixXd::Zero(OutputSize_, HiddenUnits_+1);

				// For every set
				for (unsigned set = 0; set < TrainSize_; set++) {
					//  --- Feedforward propagation ---
					std::array<MatrixXd, cNuLayers> a;
					std::array<MatrixXd, cNuLayers> z;

					// Initial activation
					a[0] = appendBias(_x.block<1, InputSize_>(set, 0));
					std::cout << a[0] << std::endl << std::endl;
					// Activations
					for (unsigned layer = 1; layer < cNuLayers; layer++) {
						z[layer] = (mParameters[layer-1]*a[layer-1].transpose()).transpose();
						if(layer == cNuLayers - 1)
							a[layer] = sigmoid(z[layer]);
						else
							a[layer] = appendBias(sigmoid(z[layer]));
					}
					std::cout << a[1] << std::endl << std::endl;
					std::cout << z[1] << std::endl << std::endl;
					std::cout << a[2] << std::endl << std::endl;
					std::cout << z[2] << std::endl << std::endl;
					// Compute cost
					auto h = a[a.size()-1];
					cost += (-_y[set]*log(h(0,0)) - (1-_y[set])*(log(1-h(0,0))));

					//  --- Back propagation ---
					std::array<MatrixXd, cNuLayers> d;

					d[2] = a[a.size()-1] - _y.block<OutputSize_, 1>(set, 0);
					d[1] = mParameters[1].block<OutputSize_, HiddenUnits_>(0, 1).cwiseProduct(d[2]*sigmoidGradient(z[1])).transpose();
					gradients[0] += d[1]*a[0];
					gradients[1] += d[2]*a[1];


					std::cout << d[2] << std::endl << std::endl;
					std::cout << d[1] << std::endl << std::endl;
					std::cout << gradients[0] << std::endl << std::endl;
					std::cout << gradients[1] << std::endl << std::endl;
				}

				cost = cost/TrainSize_;

				gradients[0] = gradients[0]/TrainSize_;
				gradients[1] = gradients[1]/TrainSize_;

				std::cout << gradients[0] << std::endl << std::endl;
				std::cout << gradients[1] << std::endl << std::endl;

				// Regularize cost function.
				Eigen::MatrixXd aux1 = mParameters[0].block<HiddenUnits_, InputSize_>(0,1);
				Eigen::MatrixXd aux2 = mParameters[1].block<OutputSize_,HiddenUnits_>(0,1);
				cost += (aux1.cwiseProduct(aux1).sum() + aux2.cwiseProduct(aux2).sum())*_lambda/2/TrainSize_;

				// Regularize gradient.
				aux1 = mParameters[0];
				aux1.block<HiddenUnits_, 1>(0,0) = Eigen::MatrixXd::Zero(HiddenUnits_,1);
				gradients[0] += _lambda/TrainSize_*aux1;

				aux2 = mParameters[1];
				aux2.block<OutputSize_, 1>(0,0) = Eigen::MatrixXd::Zero(OutputSize_,1);
				gradients[1] += _lambda/TrainSize_*aux2;


				std::cout << gradients[0] << std::endl << std::endl;
				std::cout << gradients[1] << std::endl << std::endl;

				mParameters[0].block<HiddenUnits_, InputSize_>(0,1) -= _alpha*gradients[0].block<HiddenUnits_, InputSize_>(0,1);
				mParameters[1].block<OutputSize_,HiddenUnits_>(0,1) -= _alpha*gradients[1].block<OutputSize_,HiddenUnits_>(0,1);
				

				std::cout << mParameters[0] << std::endl << std::endl;
				std::cout << mParameters[1] << std::endl << std::endl;

				iters++;
				std::cout << cost << std::endl;
				/*
				//lastCost = cost;
				Eigen::MatrixXd grad1 = Eigen::MatrixXd::Zero(HiddenUnits_, HiddenUnits_);
				Eigen::MatrixXd grad2 = Eigen::MatrixXd::Zero(OutputSize_, HiddenUnits_+1);

				// Traing
				for (unsigned set = 0; set < TrainSize_; set++) {
					// Feedforward Propagation
					std::array<MatrixXd, HiddenLayers_ + 2> a;
					std::array<MatrixXd, HiddenLayers_ + 2> z;

					// a1
					a[0] = Eigen::MatrixXd(1, InputSize_+1);
					a[0](0,0) = 1;
					a[0].block<1, InputSize_>(0, 1) = _x.block<1, InputSize_>(set, 0);
					a[0].transposeInPlace();
					// z2
					z[0] = Theta1*a[0];

					// a2
					a[1] = Eigen::MatrixXd(1, HiddenUnits_+1);
					a[1](0,0)  = 1;
					a[1].block<1, HiddenUnits_>(0, 1) = sigmoid(z[0]).transpose();
					a[1].transposeInPlace();
				
					// z3
					z[1] = ThetaN*a[1];

					// h = y
					Eigen::MatrixXd h = sigmoid(z[1]);
					cost += (-_y[set]*log(h(0,0)) - (1-_y[set])*(log(1-h(0,0))));

					// Backpropagation
					std::array<MatrixXd, HiddenLayers_ + 2> d;

					d[2] = h - _y.block<OutputSize_, 1>(set, 0);
					d[1] = ThetaN.block<OutputSize_, HiddenUnits_>(0, 1).transpose()*d[2]*sigmoidGradient(z[1]);
					grad1 += d[1]*a[0].transpose();
					grad2 += d[2]*a[1].transpose();
				}
				cost = cost/TrainSize_;

				grad1 = grad1/TrainSize_;
				grad2 = grad2/TrainSize_;

				iters++;
				// Regularize cost function.
				Eigen::MatrixXd aux1 = Theta1.block<HiddenUnits_, InputSize_>(0,1);
				Eigen::MatrixXd aux2 = ThetaN.block<OutputSize_,HiddenUnits_>(0,1);
				cost += (aux1.cwiseProduct(aux1).sum() + aux2.cwiseProduct(aux2).sum())*_lambda/2/TrainSize_;

				// Regularize gradient.
				aux1 = Theta1;
				aux1.block<HiddenUnits_, 1>(0,0) = Eigen::MatrixXd::Zero(HiddenUnits_,1);
				grad1 += _lambda/TrainSize_*aux1;

				aux2 = ThetaN;
				aux2.block<OutputSize_, 1>(0,0) = Eigen::MatrixXd::Zero(OutputSize_,1);
				grad2 += _lambda/TrainSize_*aux2;

				Theta1.block<HiddenUnits_, InputSize_>(0,1) -= _alpha*grad1.block<HiddenUnits_, InputSize_>(0,1);
				ThetaN.block<OutputSize_,HiddenUnits_>(0,1) -= _alpha*grad2.block<OutputSize_,HiddenUnits_>(0,1);*/
			}while(iters < _maxIter/* && abs(lastCost - cos) > _tol*/);
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_, unsigned HiddenLayers_, unsigned HiddenUnits_, unsigned OutputSize_>
		Eigen::Matrix<double, OutputSize_, 1> NeuronalNetwork<InputSize_, HiddenLayers_, HiddenUnits_, OutputSize_>::evaluate(const Eigen::Matrix<double, InputSize_, 1> &_x) {
			// Feedforward Propagation
			std::array<MatrixXd, HiddenLayers_ + 2> a;
			std::array<MatrixXd, HiddenLayers_ + 2> z;

			// a1
			a[0] = Eigen::MatrixXd(1, InputSize_+1);
			a[0](0,0) = 1;
			a[0].block<1, InputSize_>(0, 1) = _x;
			a[0].transposeInPlace();
			// z2
			z[0] = mParameters[0]*a[0];

			// a2
			a[1] = Eigen::MatrixXd(1, HiddenUnits_+1);
			a[1](0,0)  = 1;
			a[1].block<1, HiddenUnits_>(0, 1) = sigmoid(z[0]).transpose();
			a[1].transposeInPlace();

			// z3
			z[1] = mParameters[1]*a[1];

			// h = y
			Eigen::MatrixXd h = sigmoid(z[1]);

			return h;
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_, unsigned HiddenLayers_, unsigned HiddenUnits_, unsigned OutputSize_>
		std::array<Eigen::MatrixXd, HiddenLayers_ -1 +2> NeuronalNetwork<InputSize_, HiddenLayers_, HiddenUnits_, OutputSize_>::parameters(){
			std::array<Eigen::MatrixXd, HiddenLayers_ -1 +2> params;
			params[0] = Theta1;
			params[params.size()-1] = ThetaN;
			for (unsigned i = 0; i < HiddenLayers_ - 1; i++) {
				params[i] = ThetaI[i];
			}
			return params;
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
			Eigen::MatrixXd x(_x.rows(), _x.cols() + 1);
			x(0, 0) = 1;
			x.block(0, 1, 1, _x.cols()) = _x;
			return x;
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