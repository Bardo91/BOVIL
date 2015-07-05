///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include <Eigen/Eigen>
#include <algorithms/machine_learning/Polynomial.h>

using namespace Eigen;
using namespace BOViL::algorithms;

int main(int _argc, char** _argv) {

	// Polynomial creation.
	// ex: y = 1 + 2*x1 + x1^2 + x2^2;
	std::function<Eigen::Matrix<double, 4, 1>(Eigen::Matrix<double, 1, 2>)> base = [](Eigen::Matrix<double, 1, 2> _x) {
		Eigen::Matrix<double, 4, 1> base;
		base << 1, _x(0), pow(_x(2), 2), pow(_x(1), 2);
		return base;
	};

	Polynomial<2,4> pol1(base);

	// Setting params.
	Eigen::Matrix<double, 4, 1> params;
	params << 1, 2, 1, 1;
	pol1.setParams(params);

	// Evaluate y(1,2)
	Eigen::Matrix<double, 1, 2> x;
	x << 1, 2;

	double y = pol1.evaluate(x);

	assert(8 == y);

}
