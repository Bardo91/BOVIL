/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test_cases
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-25
//
/////////////////////////////////////////////////////////////////////////////////////////


#include "testCaseGroundEKF.h"
#include <core/math/Matrix.h>
#include <algorithms/state_estimators/GroundTrackingEKF.h>
#include <core/math/geometrics/Geometrics.h>

#include <iostream>
#include <fstream>

static const double arrayQ[16] = {  0.05, 0, 0, 0,
									0, 0.05, 0, 0,
									0, 0, 0.05, 0,
									0, 0, 0, 0.05 };

static const double arrayR[4] = {	0.1, 0,
									0, 0.1 };

static const double arrayX0[4] = {	3.0,//0, 
									8.0,//0, 
									0.0,//0, 
									0.0 };//0);


using namespace BOViL::math;

void testCaseGroundEKF(){
	//-----------------------------------------------------------------------------------
	std::ofstream outFile;
	std::string pathName;
	pathName = "./outputFile_GroundTracking.txt";
	outFile.open(pathName.c_str());
	
	//-----------------------------------------------------------------------------------
	
	// Camera position
	double arrayC[3] = { 1, 1, 1 };
	Matrix<double> C(arrayC, 3, 1);

	// Target position
	double arrayP[3] = { 1, 1, 0 };
	Matrix<double> P(arrayC, 3, 1);

	// Matrix rotation
	double arrayR[9] = { 1, 0, 0,
					0, -1, 0,
					0, 0, -1 };
	Matrix<double> R = BOViL::math::createRotationMatrixEuler(3.14159,0.0,0.0);

	// Other params
	double f = 1;	// Not necessary

	double u0 = 128;	// Image's centroid
	double v0 = 128;

	double Ximg = 128;	// Target centroid
	double Yimg = 128;

	double Xp = Ximg - u0;
	double Yp = Yimg - v0;

	double arrayZk[2] = { Ximg, Yimg };
	Matrix<double> Zk(arrayZk, 2, 1);

	double Zc = (0 - C(0, 2)) / (R(2, 0)*Xp / f + R(2, 1)*Yp / f + R(2, 2));

	double arrayPc[3] = { Xp / f*Zc, Yp / f*Zc, Zc };
	Matrix<double> Pc(arrayPc, 3, 1);

	Matrix<double> triangulateP = C + R*Pc;

	std::cout << "Triangulando directamente" << std::endl;
	triangulateP.showMatrix();

	//system("PAUSE");
	
	//-----------------------------------------------------------------------------------
	std::cout << "Triangulando con el EKF" << std::endl;
	
	BOViL::algorithms::GroundTrackingEKF groundEKF;

	groundEKF.setUpEKF(Matrix<double>(arrayQ, 4, 4),
		Matrix<double>(arrayR, 2, 2),
		Matrix<double>(arrayX0, 4, 1));

	groundEKF.setUpCamera(f, u0, v0);

	while (1){
 		groundEKF.updateCamera(C, R, 0);

		groundEKF.stepEKF(Zk, 0.05);

		groundEKF.getStateVector().showMatrix();
		system("PAUSE");
	}


}