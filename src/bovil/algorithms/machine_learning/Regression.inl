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
		template<unsigned Nvars_, unsigned Nmonomials_>
		Regression<Nvars_, Nmonomials_>::Regression(const Polynomial<Nvars_, Nmonomials_> &_hypothesis, const std::function<double(double)> &_transformation): mHypothesis(_hypothesis), mTransformation(_transformation) {
			// 666 Random init of theta? watch video.
			mHypothesis.setParams(Eigen::Matrix<double, Nmonomials_,1>::Zero());
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		template<unsigned TrainSize_>
		void Regression<Nvars_, Nmonomials_>::train(const Eigen::Matrix<double, TrainSize_,Nvars_> &_x, const Eigen::Matrix<double, TrainSize_, 1> &_y, double _alpha, double _lambda, unsigned _maxIter, double _tol) {
			auto X = adaptSet<TrainSize_>(_x);
			unsigned iters = 0;
			double cos = 0.0, lastCost = 999999;
			do {
				lastCost = cos;
				Eigen::Matrix<double, 1, Nmonomials_> parameters = mHypothesis.parameters();
				Eigen::Matrix<double, Nmonomials_, 1> grad = Eigen::Matrix<double, Nmonomials_, 1>::Zero();
				for (unsigned set = 0; set < TrainSize_; set++) {
					grad = grad + gradient(X.block<1, Nmonomials_>(set,0), _y(set));
					cos += cost(X.block<1, Nmonomials_>(set,0), _y(set));
				}
				for (unsigned param = 1; param < Nmonomials_; param++) {
					grad(param) = grad(param) + _lambda*parameters(param);
					cos += _lambda*pow(parameters(param),2);
				}

				grad = grad / TrainSize_;
				cos /= TrainSize_*2;
				mHypothesis.setParams(parameters - _alpha*grad.transpose());
				iters++;
			}while(iters < _maxIter && abs(lastCost - cos) > _tol);
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		double Regression<Nvars_, Nmonomials_>::evaluate(const typename Eigen::Matrix<double, 1, Nvars_> &_x) const{
			return mTransformation(mHypothesis.evaluate(_x));
		}
		//-------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		Polynomial<Nvars_, Nmonomials_> Regression<Nvars_, Nmonomials_>::hypothesis() const{
			return mHypothesis;
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		Eigen::Matrix<double, Nmonomials_,1> Regression<Nvars_, Nmonomials_>::gradient(const Eigen::Matrix<double, 1, Nmonomials_> &_x, double _y) const{
			Eigen::Matrix<double, Nmonomials_,1> grad = Eigen::Matrix<double, Nmonomials_,1>::Zero();
			Eigen::Matrix<double, 1, Nmonomials_> params = mHypothesis.parameters();
			for (unsigned param = 0; param < Nmonomials_; param++) {
				grad(param) = (mTransformation(params*_x.transpose()) - _y)*_x(param);
			}
			return grad;
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		template <unsigned TrainSize_>
		Eigen::Matrix<double, TrainSize_,Nmonomials_> Regression<Nvars_, Nmonomials_>::adaptSet(const Eigen::Matrix<double, TrainSize_,Nvars_> &_x) const{
			Eigen::Matrix<double, TrainSize_,Nmonomials_> X;
			for (unsigned set = 0; set < TrainSize_; set++) {
				X.block<1,Nmonomials_>(set,0) = mHypothesis.monomialCalculator()(_x.row(set));
			}
			std::cout << X << std::endl;
			return X;
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		double Regression<Nvars_, Nmonomials_>::cost(const Eigen::Matrix<double, 1, Nmonomials_> &_x, double _y) const{
			return pow(mTransformation(mHypothesis.parameters()*_x.transpose()) - _y,2);
		}
	}	//	namespace algorithms
}	//	namespace BOViL
