////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

namespace BOViL {
	namespace algorithms {
		template<unsigned Nvars_, unsigned Nmonomials_>
		Polynomial<Nvars_, Nmonomials_>::Polynomial(std::function<Monomials(const Input &)> _monomials) {

		}


		template<unsigned Nvars_, unsigned Nmonomials_>
		void Polynomial<Nvars_, Nmonomials_>::setParams(const Params &_params) {

		}


		template<unsigned Nvars_, unsigned Nmonomials_>
		double Polynomial<Nvars_, Nmonomials_>::evaluate(const Input &_x) const{
			return NAN;
		}
	}	//	namespace algorithms
}	//	namespace BOViL