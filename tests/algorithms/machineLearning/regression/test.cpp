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
	// ex. y = a + b*x1 + c*x2;

	Regression<2,3>::Hypothesis hypothesis = [] (const Polynomial<2,3>::Input &_x) {
		return Polynomial<2,3>::Monomials({1, _x(0), _x(1)});
	};

	Regression<2,3> regression(hypothesis);

	Matrix<double, 2, 2> xTs({0,0,1,1});
	Matrix<double, 2, 1> yTs({0,1});

	regression.train<2>(xTs, yTs, 1.0, 0.1);

	const double tol = 0.05;
	assert(abs(0.0 - regression.evaluate({0.0, 0.0})) < tol);
	assert(abs(0.5 - regression.evaluate({0.5, 0.5})) < tol);
	assert(abs(1.0 - regression.evaluate({1.0, 1.0})) < tol);
}

//---------------------------------------------------------------------------------------------------------------------
void polinomialRegression() {
	// ex. y = a + b*x1 + c*x1^2;
	Regression<1,3>::Hypothesis hypothesis = [] (const Polynomial<1,3>::Input &_x) {
		Polynomial<1,3>::Monomials mon;
		mon << 1, _x(0), pow(_x(0),2);
		return mon;
	};

	Regression<1,3> regression(hypothesis);

	Matrix<double, 3, 1> xTs({0,1,2});
	Matrix<double, 3, 1> yTs({0, 3, 2});
	
	regression.train<3>(xTs, yTs, 0.2, 0.0, 1000);

	const double tol = 0.05;
	Matrix<double,1,1> x({0});
	assert(abs(0.0 - regression.evaluate(x)) < tol);
	Matrix<double,1,1> x({1});
	assert(abs(3.0 - regression.evaluate(x)) < tol);
	Matrix<double,1,1> x({2});
	assert(abs(2.0 - regression.evaluate(x)) < tol);

}

//---------------------------------------------------------------------------------------------------------------------
void polinomialRegressionMulti() {
	// ex. y = a + b*x1 + c*x1*x2 + d*x*2 + e*x*2^2;
	Regression<2,5>::Hypothesis hypothesis = [] (const Polynomial<2,5>::Input &_x) {
		Polynomial<2,5>::Monomials mon;
		mon << 1, _x(0), _x(0)*_x(1), _x(1), pow(_x(1),2) ;
		return mon;
	};

	Regression<2,5> regression(hypothesis);

	Matrix<double, 9, 2> xTs;
	xTs <<  0, 0,
			0, 1,
			0, 2,
			1, 0,
			1, 1,
			1, 2,
			2, 0,
			2, 1,
			2, 2;

	Matrix<double, 9, 1> yTs;
	yTs << 0.3, 0.6, 1, 0.6, 0.6, 0.65, 1.0, 0.7, 0.4;
	regression.train<9>(xTs, yTs, 0.01, 1.0, 10000, 0.000001);

	const double tol = 0.1;
	assert(abs(0.6 - regression.evaluate({1.0, 1.0})) < tol);
	assert(abs(0.65 - regression.evaluate({1.0, 2.0})) < tol);
}