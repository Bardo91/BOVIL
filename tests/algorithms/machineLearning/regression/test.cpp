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
void logisticRegression();
void logisticRegressionMulti();

int main(int _argc, char** _argv) {

	linearRegression();

	polinomialRegression();

	polinomialRegressionMulti();

	logisticRegression();

	logisticRegressionMulti();
}

//---------------------------------------------------------------------------------------------------------------------
void linearRegression() {
	// ex. y = a + b*x1 + c*x2;

	Regression<2,3>::Hypothesis hypothesis = [] (const Polynomial<2,3>::Input &_x) {
		return Polynomial<2,3>::Monomials({1, _x(0), _x(1)});
	};

	Regression<2,3> regression(hypothesis);

	Matrix<double, 2, 2> xTs;
	xTs << 0, 0, 1, 1;
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
	Matrix<double,1,1> x;
	x << 0;
	assert(abs(0.0 - regression.evaluate(x)) < tol);
	Matrix<double,1,1> y;
	y << 1;
	assert(abs(3.0 - regression.evaluate(y)) < tol);
	Matrix<double,1,1> z;
	z << 2;
	assert(abs(2.0 - regression.evaluate(z)) < tol);

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

//---------------------------------------------------------------------------------------------------------------------
void logisticRegression() {
	// ex. y = a + b*x1 + c*x1^2 + d*x1^3;
	Regression<1,4>::Hypothesis hypothesis = [] (const Polynomial<1,4>::Input &_x) {
		Polynomial<1,4>::Monomials mon;
		mon << 1, _x(0), pow(_x(0),2), pow(_x(0),3);
		return mon;
	};

	auto sigmoid = [](double _x) {
		return 1/(1 + exp(-_x));
	};

	Regression<1,4> regression(hypothesis, sigmoid);

	Matrix<double, 7, 1> xTs;
	xTs << 0, 0.25, 0.5, 1, 1.5, 1.75, 2;
	Matrix<double, 7, 1> yTs;
	yTs << 0, 0, 1, 1, 1, 0, 0;

	regression.train<7>(xTs, yTs, 0.2, 0.0, 1000);

	Matrix<double,1,1> x;
	x << 0.2;
	assert(regression.evaluate(x) < 0.5);
	Matrix<double,1,1> y;
	y << 1.25;
	assert(regression.evaluate(y) > 0.5);
	Matrix<double,1,1> z;
	z << 1.8;
	assert(regression.evaluate(z) < 0.5);
}

//---------------------------------------------------------------------------------------------------------------------
void logisticRegressionMulti() {
	// ex. y = a + b*x1 + c*x1*x2 + d*x2 + e*x2^2
	Regression<2,6>::Hypothesis hypothesis = [] (const Polynomial<2,6>::Input &_x) {
		Polynomial<2,6>::Monomials mon;
		mon << 1, _x(0), _x(0)*_x(0), _x(0)*_x(1), _x(1), pow(_x(1),2);
		return mon;
	};

	auto sigmoid = [](double _x) {
		return 1/(1 + exp(-_x));
	};

	Regression<2,6> regression(hypothesis, sigmoid);

	Matrix<double, 25, 2> xTs;
	xTs <<	0, 0,	// y = 0.
			0, 0.5,	// y = 0.
			0, 1,	// y = 0.
			0, 1.5,	// y = 0.
			0, 2,	// y = 0.
			2, 0,	// y = 0.
			2, 0.5,	// y = 0.
			2, 1,	// y = 0.
			2, 1.5,	// y = 0.
			2, 2,	// y = 0.
			0.5, 0,	// y = 0.
			1, 0,	// y = 0.
			1.5, 0,	// y = 0.
			0.5, 2,	// y = 0.
			1, 2,	// y = 0.
			1.5, 2,	// y = 0.
			0.75, 0.75,	// y = 1.
			0.75, 1,	// y = 1.
			0.75, 1.25,	// y = 1.
			1, 0.75,	// y = 1.
			1, 1,		// y = 1.
			1, 1.25,	// y = 1.
			1.25, 0.75,	// y = 1.
			1.25, 1,	// y = 1.
			1.25, 1.25;	// y = 1.

	Matrix<double, 25, 1> yTs;
	yTs << 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1;

	regression.train<25>(xTs, yTs, 0.2, 0.0, 1000);

	Matrix<double, 1, 2> x({1.2, 1.3});
	assert(regression.evaluate(x) > 0.5);
	Matrix<double, 1, 2> y({0.3, 1.9});
	assert(regression.evaluate(y) < 0.5);
}