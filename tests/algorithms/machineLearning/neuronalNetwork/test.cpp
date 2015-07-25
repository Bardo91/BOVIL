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
void irisNN();

int main(int _argc, char** _argv) {

	simpleNN();

	wineNN();

	irisNN();
}

void simpleNN() {
	// Simple nn with 4 input units 1 output unit and 1 hidden layer with 4 units.
	NeuronalNetwork<4,1,4,1> nn;

	Matrix<double, 7, 4> xSet;
	xSet << 1, 0, 0,0.1,
		1, 0.5, 0,0,
		1, 1, 0,0,
		0, 0, 0,0,
		0, 0, 0.5,0,
		0, 0, 1,0,
		0, 0.5, 1,0;
	Matrix<double, 7, 1> ySet;
	ySet << 1, 1, 1, 0, 0, 0, 0;
	nn.train(xSet, ySet, 1, 0.1);

	Matrix<double, 4, 1> x1({0.8, 0.5, 0, 0});
	Matrix<double, 1, 1> y1 = nn.evaluate(x1);
	assert(y1(0,0) > 0.5);

	Matrix<double, 4, 1> x2({0, 0, 0.8, 0});
	Matrix<double, 1, 1> y2 = nn.evaluate(x2);
	assert(y2(0,0) < 0.5);
}

template<unsigned TrainSize_, unsigned InputSize_, unsigned OutputSize_>
void loadDataset(Matrix<double, TrainSize_,InputSize_> &_xSet, Matrix<double, TrainSize_,OutputSize_> &_ySet, std::string _file) {
	std::ifstream dataFile(_file);
	assert(dataFile.is_open());
	std::string line;
	unsigned i = 0;
	_ySet = Matrix<double, TrainSize_,OutputSize_>::Zero();
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

template<unsigned InputSize_, unsigned HiddenLayers_, unsigned HiddenUnits_, unsigned OutputSize_,unsigned TrainSize_>
double accuracy(const Matrix<double, TrainSize_,InputSize_> &_xSet, const Matrix<double, TrainSize_,OutputSize_> &_ySet, NeuronalNetwork<InputSize_, HiddenLayers_, HiddenUnits_, OutputSize_> &_nn) {
	
	double accuracy = 0.0;
	for (unsigned set = 0; set < TrainSize_; set++) {
		Eigen::MatrixXd x = _xSet.block<1, InputSize_>(set,0);
		Eigen::MatrixXd y = _nn.evaluate(x.transpose());

		// Get index of max probability
		unsigned index = 0;
		double prob = 0.0;
		for (int i = 0; i < y.rows(); i++) {
			if (y(i) > prob) {
				prob = y(i);
				index = i;
			}
		}

		accuracy += _ySet(set, index);
	}

	return accuracy/TrainSize_;

}

void wineNN() {
	NeuronalNetwork<13,1,20,3> nn;

	Matrix<double, 178,13> xSet;
	Matrix<double, 178,3> ySet;
	loadDataset<178,13,3>(xSet, ySet, "wineDataset.txt");

	nn.train(xSet, ySet, 1.0, 0.1);

	Matrix<double, 13, 1> x1;
	x1 << 13.75,1.73,2.41,16,89,2.6,2.76,.29,1.81,5.6,1.15,2.9,1320;
	Matrix<double, 1, 3> y1 = nn.evaluate(x1);	// y ~ [1 0 0] ;
	assert(y1(0) > 0.5);
	assert(y1(1) + y1(2) < 0.5);

	Matrix<double, 13, 1> x2;
	x2 << 12.42,1.61,2.19,22.5,108,2,2.09,.34,1.61,2.06,1.06,2.96,345;
	Matrix<double, 1, 3> y2 = nn.evaluate(x2);	// y ~ [0 1 0] ;
	assert(y2(1) > 0.5);
	assert(y2(0) + y2(2) < 0.5);

	Matrix<double, 13, 1> x3;
	x3 << 13.08,3.9,2.36,21.5,113,1.41,1.39,.34,1.14,9.40,.57,1.33,550;
	Matrix<double, 1, 3> y3 = nn.evaluate(x3);	// y ~ [0 0 1] ;
	assert(y3(2) > 0.5);
	assert(y3(0) + y3(1) < 0.5);

	double acc = accuracy<13,1,20,3,178>(xSet, ySet, nn);
	assert(acc > 0.9);	//	 = 1;
}

void irisNN() {
	NeuronalNetwork<4,1,20,3> nn;

	Matrix<double, 150,4> xSet;
	Matrix<double, 150,3> ySet;
	loadDataset<150,4,3>(xSet, ySet,"irisDataset.txt");

	nn.train(xSet, ySet, 1.0, 0.1);

	Matrix<double, 4, 1> x1;
	x1 << 4.7,3.2,1.3,0.2;
	Matrix<double, 1, 3> y1 = nn.evaluate(x1);	// y ~ [1 0 0] ;
	assert(y1(0) > 0.5);
	assert(y1(1) + y1(2) < 0.5);

	Matrix<double, 4, 1> x2;
	x2 << 4.9,2.4,3.3,1.0;
	Matrix<double, 1, 3> y2 = nn.evaluate(x2);	// y ~ [0 1 0] ;
	assert(y2(1) > 0.5);
	assert(y2(0) + y2(2) < 0.5);

	Matrix<double, 4, 1> x3;
	x3 << 7.7,3.0,6.1,2.3;
	Matrix<double, 1, 3> y3 = nn.evaluate(x3);	// y ~ [0 0 1] ;
	assert(y3(2) > 0.5);
	assert(y3(0) + y3(1) < 0.5);

	double acc = accuracy<4,1,20,3,150>(xSet, ySet, nn);
	assert(acc > 0.9);	//	 ~0.94
}