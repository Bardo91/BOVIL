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
	typedef Polynomial<2,4> SquarePol;

	SquarePol pol1(
		[](const SquarePol::Input &_x) {
			return SquarePol::Monomials({ 1, _x(0), pow(_x(0), 2), pow(_x(1), 2) });
		}
	);

	// Setting params.
	pol1.setParams({ 1, 2, 1, 1 });

	// Evaluate y(1,2)
	double y = pol1.evaluate({ 1, 2 });

	assert(8 == y);

}
