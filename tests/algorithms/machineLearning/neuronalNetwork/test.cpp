///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include <cassert>
#include <Eigen/Eigen>
#include <algorithms/machine_learning/NeuronalNetwork.h>

#include <iostream>

using namespace Eigen;
using namespace BOViL::algorithms;

int main(int _argc, char** _argv) {

	// Simple nn with 3 input units 1 output unit and 1 hidden layer with 4 units.
	NeuronalNetwork<3,1,4,1> nn;

	Matrix<double, 6, 3> xSet;
	xSet << 1, 0, 0,
			1, 0.5, 0,
			1, 1, 0,
			0, 0, 0,
			0, 0, 0.5,
			0, 0, 1;
	Matrix<double, 6, 1> ySet;
	ySet << 1, 1, 1, 0, 0, 0;
	nn.train<6>(xSet, ySet, 1, 0.1);

	Matrix<double, 3, 1> x1({0.8, 0.5, 0});
	Matrix<double, 1, 1> y1 = nn.evaluate(x1); // ~ 0.764835
	//assert(y1(0,0) > 0.5);
	std::cout << y1 << std::endl<< std::endl;

	Matrix<double, 3, 1> x2({0, 0, 0.8});
	Matrix<double, 1, 1> y2 = nn.evaluate(x2);	// ~ 0.133156
	//assert(y2(0,0) < 0.5);
	std::cout << y2 << std::endl<< std::endl;
}