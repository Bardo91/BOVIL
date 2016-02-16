////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

namespace BOViL {
	namespace algorithms {
		//-------------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		Polynomial<Nvars_, Nmonomials_>::Polynomial(std::function<Monomials(const Input &)> _monomials): mMonomialCalculator(_monomials) {
		}

		//-------------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		void Polynomial<Nvars_, Nmonomials_>::setParams(const Params &_params) {
			mParams = _params;
		}

		//-------------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		double Polynomial<Nvars_, Nmonomials_>::evaluate(const Input &_x) const{
			Monomials monom = mMonomialCalculator(_x);
			return mParams*monom;
		}

		//-------------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		Eigen::Matrix<double, 1, Nmonomials_> Polynomial<Nvars_, Nmonomials_>::parameters() const {
			return mParams;
		}

		//-------------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>		
		std::function<Eigen::Matrix<double, Nmonomials_, 1>(const Eigen::Matrix<double, 1, Nvars_> &)> Polynomial<Nvars_, Nmonomials_>::monomialCalculator() const {
			return mMonomialCalculator;
		}
	}	//	namespace algorithms
}	//	namespace BOViL