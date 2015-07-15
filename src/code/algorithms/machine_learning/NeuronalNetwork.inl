///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

namespace BOViL {
	namespace algorithms {
		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_, unsigned HiddenLayers_, unsigned HiddenUnits_, unsigned OutputSize_>
		template<unsigned TrainSize_>
		void NeuronalNetwork<InputSize_, HiddenLayers_, HiddenUnits_, OutputSize_>::train(const Eigen::Matrix<double, TrainSize_, InputSize_> &_x, const Eigen::Matrix<double, TrainSize_, OutputSize_> &_y, double _alpha, double _lambda, unsigned _maxIter, double _tol) {
			const int cNuLayers = HiddenLayers_ + 2;
			// Init params randomlly to decouple params.
			randomizeParams();
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
					// Activations
					for (unsigned layer = 1; layer < cNuLayers; layer++) {
						z[layer] = (mParameters[layer-1]*a[layer-1].transpose()).transpose();
						if(layer == cNuLayers - 1)
							a[layer] = sigmoid(z[layer]);
						else
							a[layer] = appendBias(sigmoid(z[layer]));
					}
					// Compute cost
					Eigen::MatrixXd h = a[a.size()-1];
					cost += -( _y.block<1, OutputSize_>(set,0)*logarithm(h)+ (Eigen::MatrixXd::Ones(1, OutputSize_) - _y.block<1, OutputSize_>(set,0)*logarithm(Eigen::MatrixXd::Ones(1, OutputSize_) - h))).sum();

					//  --- Back propagation ---
					std::array<MatrixXd, cNuLayers> d;

					d[a.size()-1] = a[a.size()-1] - _y.block<OutputSize_, 1>(set, 0);
					for (unsigned i = cNuLayers - 2; i > 0; i--) {
						d[i] = mParameters[i].block<OutputSize_, HiddenUnits_>(0, 1).cwiseProduct(d[i+1]*sigmoidGradient(z[i])).transpose();
					}

					for (unsigned i = 0; i < cNuLayers - 1; i++) {
						gradients[i] += d[i+1]*a[i];
					}
				}
				cost = cost/TrainSize_;
				for (unsigned i = 0; i < cNuLayers - 1; i++) {
					gradients[i] /= TrainSize_;
				}

				// Regularize cost function.
				for (unsigned i = 0; i < cNuLayers-1; i++) {
					Eigen::MatrixXd aux = mParameters[i].block(0,1, mParameters[i].rows(), mParameters[i].cols()-1);
					cost += aux.cwiseProduct(aux).sum();
				}
				cost *= _lambda/2/TrainSize_;

				// Regularize gradient.
				for (unsigned i = 0; i < cNuLayers-1; i++) {
					auto aux = mParameters[i];
					aux.block(0,0,mParameters[i].rows(), 1) = Eigen::MatrixXd::Zero(mParameters[i].rows(),1);
					gradients[i] += _lambda/TrainSize_*aux;
				}

				for (unsigned i = 0; i < cNuLayers-1; i++) {
					mParameters[i].block(0,1, mParameters[i].rows(), mParameters[i].cols()-1) += - _alpha*gradients[i].block(0,1, gradients[i].rows(), gradients[i].cols()-1);
				}
				iters++;
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