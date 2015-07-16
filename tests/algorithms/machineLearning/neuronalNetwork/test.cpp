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
#include <fstream>

using namespace Eigen;
using namespace BOViL::algorithms;

void simpleNN();
void wineNN();

int main(int _argc, char** _argv) {

	//simpleNN();

	wineNN();
}

void simpleNN() {
	// Simple nn with 4 input units 1 output unit and 1 hidden layer with 4 units.
	NeuronalNetwork<4,1,4,1> nn;

	Matrix<double, 7, 4> xSet;
	xSet << 1, 0, 0,0,
		1, 0.5, 0,0,
		1, 1, 0,0,
		0, 0, 0,0,
		0, 0, 0.5,0,
		0, 0, 1,0,
		0, 0.5, 1,0;
	Matrix<double, 7, 1> ySet;
	ySet << 1, 1, 1, 0, 0, 0, 0;
	nn.train<7>(xSet, ySet, 1, 0.1);

	Matrix<double, 4, 1> x1({0.8, 0.5, 0, 0});
	Matrix<double, 1, 1> y1 = nn.evaluate(x1);
	assert(y1(0,0) > 0.5);

	Matrix<double, 4, 1> x2({0, 0, 0.8, 0});
	Matrix<double, 1, 1> y2 = nn.evaluate(x2);
	assert(y2(0,0) < 0.5);
}

void loadDataset(Matrix<double, 178,13> &_xSet, Matrix<double, 178,3> &_ySet);

void wineNN() {
	NeuronalNetwork<13,1,13,3> nn;

	Matrix<double, 178,13> xSet;
	Matrix<double, 178,3> ySet;
	loadDataset(xSet, ySet);

	nn.train<178>(xSet, ySet, 1.0, 0.1);

	/*Matrix<double, 13, 1> x;
	x << 13.08,3.9,2.36,21.5,113,1.41,1.39,.34,1.14,9.40,.57,1.33,550;
	Matrix<double, 1, 1> y = nn.evaluate(x);
	std::cout << y << std::endl;*/

}

void loadDataset(Matrix<double, 178,13> &_xSet, Matrix<double, 178,3> &_ySet) {
	std::ifstream dataFile("wineDataset.txt");
	assert(dataFile.is_open());
	std::string line;
	unsigned i = 0;
	_ySet = Matrix<double, 178,3>::Zero();
	while(std::getline(dataFile, line)) {
		// Get result
		int index = line.find(",");
		_ySet(i,atoi(line.substr(0,index).c_str())-1) = 1;
		line = line.substr(index+1);

		// Get inputs
		int j = 0;
		do {
			int index = line.find(",");
			_xSet(i,j) = atof(line.substr(0,index).c_str());
			line = line.substr(index+1);
			j++;
		}while(line.find(",") != std::string::npos);
		_xSet(i,j) = atof(line.c_str());
		i++;
	}
	dataFile.close();
}