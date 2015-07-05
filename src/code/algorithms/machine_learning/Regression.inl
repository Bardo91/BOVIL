///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

namespace BOViL {
	namespace algorithms {
		//-------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		Regression<Nvars_, Nmonomials_>::Regression(const Polynomial<Nvars_, Nmonomials_> &_hypothesis): mHypothesys(_hypothesis) {
			// 666 Random init of theta? watch video.
			mHypothesys.setParams(Eigen::Matrix<double, Nmonomials_,1>::Zero());
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		template<unsigned TrainSize_>
		void Regression<Nvars_, Nmonomials_>::train(const Eigen::Matrix<double, TrainSize_,Nmonomials_> &_x, const Eigen::Matrix<double, TrainSize_, 1> &_y, double _alpha, double _lambda, unsigned _maxIter) {
			unsigned iters = 0;
			do {
				Eigen::Matrix<double, 1, Nmonomials_> parameters = mHypothesys.parameters();
				Eigen::Matrix<double, Nmonomials_, 1> grad = Eigen::Matrix<double, Nmonomials_, 1>::Zero();
				for (unsigned set = 0; set < TrainSize_; set++) {
					grad = grad + gradient(_x.block<1, Nmonomials_>(set,0), _y(set));
				}
				for (unsigned param = 1; param < Nmonomials_; param++) {
					grad(param) = grad(param) + _lambda*pow(parameters(param),2);
				}

				grad = grad / TrainSize_;
				mHypothesys.setParams(parameters - _alpha*grad.transpose());
				iters++;
			}while(iters < _maxIter);
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		double Regression<Nvars_, Nmonomials_>::evaluate(const typename Eigen::Matrix<double, 1, Nvars_> &_x) const{
			return mHypothesys.evaluate(_x);
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		Eigen::Matrix<double, Nmonomials_,1> Regression<Nvars_, Nmonomials_>::gradient(const Eigen::Matrix<double, 1, Nmonomials_> &_x, double _y) const{
			Eigen::Matrix<double, Nmonomials_,1> grad = Eigen::Matrix<double, Nmonomials_,1>::Zero();
			Eigen::Matrix<double, 1, Nmonomials_> params = mHypothesys.parameters();
			for (unsigned param = 0; param < Nmonomials_; param++) {
				grad(param) = (params*_x.transpose() - _y)*_x(param);
			}
			return grad;
		}

	}	//	namespace algorithms
}	//	namespace BOViL
