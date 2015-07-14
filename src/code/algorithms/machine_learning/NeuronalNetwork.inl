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
				std::cout  << cost << std::endl;

				grad1 = grad1/TrainSize_;
				grad2 = grad2/TrainSize_;
				
				Theta1.block<HiddenUnits_, InputSize_>(0,1) += _alpha*grad1.block<HiddenUnits_, InputSize_>(0,1);
				ThetaN.block<OutputSize_,HiddenUnits_>(0,1) += _alpha*grad2.block<OutputSize_,HiddenUnits_>(0,1);

				iters++;
				// Regularize cost function.
				// Regularize gradient.
			}while(iters < _maxIter/* && abs(lastCost - cos) > _tol*/);
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_, unsigned HiddenLayers_, unsigned HiddenUnits_, unsigned OutputSize_>
		Eigen::Matrix<double, OutputSize_, 1> NeuronalNetwork<InputSize_, HiddenLayers_, HiddenUnits_, OutputSize_>::evaluate(const Eigen::Matrix<double, InputSize_, 1> &_x) {
			Eigen::Matrix<double, OutputSize_, 1> y;
			return y;
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
			Theta1 = Eigen::Matrix<double, HiddenUnits_, InputSize_ + 1>::Random();
			Theta1.block<HiddenUnits_, 1>(0,0) = Eigen::Matrix<double,HiddenUnits_, 1>::Ones();
			ThetaN = Eigen::Matrix<double, OutputSize_,HiddenUnits_ + 1> ::Random();
			ThetaN.block<OutputSize_, 1>(0,0) = Eigen::Matrix<double,OutputSize_, 1>::Ones();
			for (unsigned i = 0; i < HiddenLayers_ - 1; i++) {
				ThetaI[i] = Eigen::Matrix<double, HiddenUnits_, HiddenUnits_+1>::Random();
				ThetaI[i].block<HiddenUnits_, 1>(0,0) = Eigen::Matrix<double,HiddenUnits_, 1>::Ones();
			}
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