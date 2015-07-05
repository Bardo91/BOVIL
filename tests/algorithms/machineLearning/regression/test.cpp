///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include <Eigen/Eigen>
#include <algorithms/machine_learning/Regression.h>

using namespace Eigen;
using namespace BOViL::algorithms;

void linearRegression();
void polinomicRegression();

int main(int _argc, char** _argv) {

	linearRegression();

	polinomicRegression();
}

//---------------------------------------------------------------------------------------------------------------------
void linearRegression() {
	// ex. y = a + b*x1 + c*x*2;
	typedef Polynomial<2,3> lineal2x;

	lineal2x hypothesis(
		[] (const lineal2x::Input &_x) {
		return lineal2x::Monomials({1, _x(0), _x(1)});
		}
	);

	Regression<2,3> regression(hypothesis);

	Matrix<double, 2, 3> xTs;
	xTs << 1, 0, 0, 1, 1, 1;
	Matrix<double, 2, 1> yTs({0, 1});
	regression.train<2>(xTs, yTs, 0.5, 1.0);

	double y = regression.evaluate({0.5, 0.5});
	assert(0.5 == y);
}

//---------------------------------------------------------------------------------------------------------------------
void polinomicRegression() {
	// ex. y = a + b*x1 + c*x1*x2 + d*x*2 + e*x2^2;
	typedef Polynomial<2,5> pol2x;

	pol2x hypothesis(
		[] (const pol2x::Input &_x) {
		pol2x::Monomials mon;
		mon << 1, _x(0), _x(0)*_x(1), _x(1), pow(_x(1),2);
		return mon;
	}
	);

	Regression<2,5> regression(hypothesis);

	Matrix<double, 2, 5> xTs;
	xTs << 1, 0, 0, 0, 0, 1, 1, 1, 1, 1;
	Matrix<double, 2, 1> yTs;
	yTs <<  0, 1;
	regression.train<2>(xTs, yTs, 0.5, 1.0);

	double y = regression.evaluate({0.5, 0.5});
	//assert(0.5 == y);
}