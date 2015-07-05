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
		bool Regression<Nvars_, Nmonomials_>::train(const Eigen::Matrix<double, TrainSize_,Nmonomials_> &_x, const Eigen::Matrix<double, TrainSize_, 1> &_y, double _alpha, double _lambda, unsigned _maxIter) {
			unsigned iters = 0;
			do {
				auto parameters = mHypothesys.parameters();
				Eigen::Matrix<double, Nmonomials_, 1> grad = Eigen::Matrix<double, Nmonomials_, 1>::Zero();
				for (unsigned set = 0; set < TrainSize_; set++) {
					grad = grad + gradient(_x.block<1, Nmonomials_>(set,1), _y(set));
				}
				for (unsigned param = 1; param < Nmonomials_; param++) {
					grad(param) = grad(param) + _lambda*pow(parameters(param),2);
				}

				grad = grad / TrainSize_;
				mHypothesys.setParams(parameters - _alpha*grad);
				iters++;
			}while(iters < _maxIter);

			return false;
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		double Regression<Nvars_, Nmonomials_>::evaluate(const typename Eigen::Matrix<double, 1, Nvars_> &_x) const{
			return mHypothesys.evaluate(_x);
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		Eigen::Matrix<double, Nmonomials_,1> Regression<Nvars_, Nmonomials_>::gradient(const Eigen::Matrix<double, 1, Nmonomials_> &_x, double _y) const{
			Eigen::Matrix<double, Nmonomials_,1> grad;
			auto monomialCalculator = mHypothesys.monomialCalculator();
			auto monomials = monomialCalculator(_x);
			for (unsigned param = 0; param < Nmonomials_; param++) {
				grad(param) = (mHypothesys.evaluate(_x) - _y)*monomials(param);
			}
			return grad;
		}

	}	//	namespace algorithms
}	//	namespace BOViL
