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
	// ex. y = a + b*x1 + x*2;
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
	assert(regression.train<2>(xTs, yTs, 0.5, 1.0));


	
	lineal2x::Input x({0.5, 0.5});
	double y = regression.evaluate(x);

	assert(0.5 == y);
}

//---------------------------------------------------------------------------------------------------------------------
void polinomicRegression() {
	

}