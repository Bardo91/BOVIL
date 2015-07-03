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
	Matrix2d polinom;
	polinom << 1, 0, 0, 1;
	Regression<2> regression(polinom);

	Matrix2d xTs;
	xTs << 0, 0, 1, 1;
	Matrix<double,2,1> yTs;
	yTs << 0, 1;
	assert(regression.train<2>(xTs, yTs));


	Matrix<double, 2, 1> x;
	x << 0.5, 0.5;
	double y = regression.evaluate(x);

	assert(0.5 == y);
}

//---------------------------------------------------------------------------------------------------------------------
void polinomicRegression() {
	Matrix2d polinom;
	polinom << 2, 0, 0, 2;
	Regression<2> regression(polinom);

	Matrix<double, 3, 2> xTs;
	xTs << 0, 0, 1, 1, 1, 0;
	Matrix<double,3,1> yTs;
	yTs << 0, 1, 0;
	assert(regression.train<3>(xTs, yTs));


	Matrix<double, 2, 1> x;
	x << 1.0, 1.0;
	double y = regression.evaluate(x);

}