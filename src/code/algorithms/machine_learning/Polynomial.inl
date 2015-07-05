////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include "Polynomial.h"

namespace BOViL {
	namespace algorithms {
		template<unsigned Nvars_, unsigned Nmonomials_>
		Polynomial::Polynomial(std::function<Eigen::Matrix<double, Nmonomials_, 1>(Eigen::Matrix<double, 1, Nvar_>)> _base) {

		}


		template<unsigned Nvars_, unsigned Nmonomials_>
		Polynomial::setParams(Eigen::Matrix<double, 1, Nmonomials_>) {

		}


		template<unsigned Nvars_, unsigned Nmonomials_>
		Polynomial::evaluate(Eigen::Matrix<double, 1, Nvar_>) {

		}
	}	//	namespace algorithms
}	//	namespace BOViL