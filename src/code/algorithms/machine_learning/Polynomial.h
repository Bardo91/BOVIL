////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _BOVIL_ALGORITHMS_MACHINELEARNING_POLYNOMIAL_H_
#define _BOVIL_ALGORITHMS_MACHINELEARNING_POLYNOMIAL_H_

#include <Eigen/Eigen>
#include <functional>

namespace BOViL {
	namespace algorithms {
		/// Base template for multivariable polynomial representation
		///	\tparam Nvar_	number of variables.
		///	\tparam Size_	number of elements / Number of parameters.
		///
		///		ex. y = a*x1 +  b*x1^2 + c*x1*x2 + d*x2^2
		///				Nvar_ = 2.
		///				Size_ = 4.
		///
		template<unsigned Nvars_, unsigned Nmonomials_>
		class Polynomial {
		public:
			/// Redefinitions to simplify usage.
			typedef Eigen::Matrix<double, 1, Nvar_>			Input;
			typedef Eigen::Matrix<double, Nmonomials_, 1>	Monomials;
			typedef Eigen::Matrix<double, 1, Nmonomials_>	Params;

			/// Polynomial Constructor. 
			/// \param _base: base form of polynomial
			///
			///		ex. y = a + b*x1 +  c*x1^2 + d*x1*x2 + e*x2^2
			///		auto base = [] (double _x1, double _x2)
			///		{
			///			Eigen::Matrix\<double, 2, 5\> baseVec;
			///			base << 1		<--- x0 = 1 always.
			///					_x1,
			///					_x1^2,
			///					_x1*x2,
			///					_x2^2;
			///			return baseVec;
			///		}
			///		Polynomial\<2,5\> poly(base);
			///
			Polynomial(std::function<Monomials(Input)> _monomials);

			/// Define params of the polymonial equation.
			///
			///		ex. y = 1 + x1 +  -3*x1^2 + 8*x1*x2 + x2^2
			///		Eigen::Matrix\<double, 1, 5\> params;
			///		params << 1, 1, -3, 8, 1;
			///		poly.setParams(params);
			///
			void setParams(Params _params);

			///	Evaluate polynomial equation with the given values of variables
			///		
			///		ex. y = 1 + x1 +  -3*x1^2 + 8*x1*x2 + x2^2
			///			y(1,2) = 19;
			///		
			///		Eigen::Matrix\<double, 1, 2\> x;
			///		x << 1, 2;
			///		y = poly.evaluate(x);
			///
			double evaluate(Input _x);

		private:

		};
	}	//	namespace algorithms
}	//	namespace BOViL

#endif	//	_BOVIL_ALGORITHMS_MACHINELEARNING_POLYNOMIAL_H_