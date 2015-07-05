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
		Polynomial<Nvars_, Nmonomials_>::Polynomial(std::function<Monomials(const Input &)> _monomials) {
			mMonomialEvaluator = _monomials;
		}

		//-------------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		void Polynomial<Nvars_, Nmonomials_>::setParams(const Params &_params) {
			mParams = _params;
		}

		//-------------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		double Polynomial<Nvars_, Nmonomials_>::evaluate(const Input &_x) const{
			Monomials monom = mMonomialEvaluator(_x);
			return mParams*monom;
		}

		//-------------------------------------------------------------------------------------------------------------------
		template<unsigned Nvars_, unsigned Nmonomials_>
		Params Polynomial<Nvars_, Nmonomials_>::parameters() const {
			return mParams;
		}

	}	//	namespace algorithms
}	//	namespace BOViL