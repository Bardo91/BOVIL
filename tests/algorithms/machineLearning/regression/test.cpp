///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include <Eigen/Eigen>
#include <algorithms/machine_learning/Regression.h>

#include <iostream>

using namespace Eigen;
using namespace BOViL::algorithms;

void linearRegression();
void polinomialRegression();

int main(int _argc, char** _argv) {

	linearRegression();

	polinomialRegression();
}

//---------------------------------------------------------------------------------------------------------------------
void linearRegression() {
	// ex. y = a + b*x1 + c*x*2;
	typedef Polynomial<2,3> lineal2x;

	auto monomials = [] (const lineal2x::Input &_x) {
		return lineal2x::Monomials({1, _x(0), _x(1)});
	};
	lineal2x hypothesis( monomials );

	Regression<2,3> regression(hypothesis);

	Matrix<double, 2, 3> xTs;
	xTs.row(0) = monomials({ 0, 0 });
	xTs.row(1) = monomials({ 1, 1});
	Matrix<double, 2, 1> yTs({0, 1});
	regression.train<2>(xTs, yTs, 1.0, 0.1);

	std::cout << xTs << std::endl << std::endl;
	std::cout << yTs << std::endl << std::endl;
	std::cout << regression.hypothesis().parameters() << std::endl << std::endl;

	const double tol = 0.05;
	assert(abs(0.0 - regression.evaluate({0.0, 0.0})) < tol);
	assert(abs(0.5 - regression.evaluate({0.5, 0.5})) < tol);
	assert(abs(1.0 - regression.evaluate({1.0, 1.0})) < tol);
}

//---------------------------------------------------------------------------------------------------------------------
void polinomialRegression() {
	// ex. y = a + b*x1 + c*x1^2;
	typedef Polynomial<1,3> polx;

	auto monomials = [] (const polx::Input &_x) {
		polx::Monomials mon;
		mon << 1, _x(0), pow(_x(0),2);
		return mon;
	};

	polx hypothesis( monomials );

	Regression<1,3> regression(hypothesis);

	Matrix<double, 3, 3> xTs;
	polx::Input x;
	x(0) = 0;
	xTs.row(0) = monomials(x);
	x(0) = 1;
	xTs.row(1) = monomials(x);
	x(0) = 2;
	xTs.row(2) = monomials(x);

	Matrix<double, 3, 1> yTs({0, 3, 2});
	regression.train<3>(xTs, yTs, 0.2, 0.0, 1000);

	std::cout << xTs << std::endl << std::endl;
	std::cout << yTs << std::endl << std::endl;
	std::cout << regression.hypothesis().parameters() << std::endl << std::endl;

	const double tol = 0.05;
	x(0) = 0;
	assert(abs(0.0 - regression.evaluate(x)) < tol);
	x(0) = 1;
	assert(abs(3.0 - regression.evaluate(x)) < tol);
	x(0) = 2;
	assert(abs(2.0 - regression.evaluate(x)) < tol);

}