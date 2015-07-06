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
void polinomialRegressionMulti();

int main(int _argc, char** _argv) {

	linearRegression();

	polinomialRegression();

	polinomialRegressionMulti();
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

	const double tol = 0.05;
	x(0) = 0;
	assert(abs(0.0 - regression.evaluate(x)) < tol);
	x(0) = 1;
	assert(abs(3.0 - regression.evaluate(x)) < tol);
	x(0) = 2;
	assert(abs(2.0 - regression.evaluate(x)) < tol);

}

//---------------------------------------------------------------------------------------------------------------------
void polinomialRegressionMulti() {
	// ex. y = a + b*x1 + c*x1*x2 + d*x*2 + e*x*2^2;
	typedef Polynomial<2,5> poly2x;

	auto monomials = [] (const poly2x::Input &_x) {
		poly2x::Monomials mon;
		mon << 1, _x(0), _x(0)*_x(1), _x(1), pow(_x(1),2) ;
		return mon;
	};
	poly2x hypothesis( monomials );

	Regression<2,5> regression(hypothesis);

	Matrix<double, 9, 5> xTs;
	xTs.row(0) = monomials({ 0, 0 });
	xTs.row(1) = monomials({ 0, 1});
	xTs.row(2) = monomials({ 0, 2});
	xTs.row(3) = monomials({ 1, 0});
	xTs.row(4) = monomials({ 1, 1});
	xTs.row(5) = monomials({ 1, 2});
	xTs.row(6) = monomials({ 2, 0});
	xTs.row(7) = monomials({ 2, 1});
	xTs.row(8) = monomials({ 2, 2});
	Matrix<double, 9, 1> yTs;
	yTs << 0.3, 0.6, 1, 0.6, 0.6, 0.65, 1.0, 0.7, 0.4;
	regression.train<9>(xTs, yTs, 0.01, 1.0, 10000, 0.000001);

	std::cout << xTs << std::endl << std::endl;
	std::cout << yTs << std::endl << std::endl;
	std::cout << regression.hypothesis().parameters() << std::endl << std::endl;

	const double tol = 0.1;
	assert(abs(0.6 - regression.evaluate({1.0, 1.0})) < tol);
	assert(abs(0.65 - regression.evaluate({1.0, 2.0})) < tol);
}