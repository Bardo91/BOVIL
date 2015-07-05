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
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		template<unsigned TrainSize_>
		bool Regression<Nvars_, Nmonomials_>::train(const Eigen::Matrix<double, TrainSize_,Nmonomials_> &_x, const Eigen::Matrix<double, TrainSize_, 1> &_y, double _alpha, double _lambda, unsigned _maxIter) {
			unsigned iters = 0;
			do {
				//Eigen::Matrix<double, Nmonomials_, 1> grad = gradient();
				//mParameters = mParameters - grad;
				iters++;
			}while(iters < _maxIter);

			return false;
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		double Regression<Nvars_, Nmonomials_>::evaluate(const typename Eigen::Matrix<double, 1, Nvars_> &_x) {
			return NAN;
		}

	}	//	namespace algorithms
}	//	namespace BOViL
