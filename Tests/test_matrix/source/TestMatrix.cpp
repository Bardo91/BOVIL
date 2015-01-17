/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-12
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "TestMatrix.h"



using namespace Eigen;
using namespace std;

void testMatrix(){
	cout << "--------- TESTING MATRIX OPERATIONS --------------" << endl;
	double matArray[9] = {	1.0, 2.0, 3.0, 
							4.0, 5.0, 6.0, 
							7.0, 8.0, 8.0	};

	cout << "Matrix creation" << endl;
	Matrix<double, 3, 3> mat;
	cout << mat << endl;


	mat <<	1.0, 2.0, 3.0,
			4.0, 5.0, 6.0,
			7.0, 8.0, 8.0;
	cout << mat << endl;

	cout << "------------" << endl;
	cout << "Matrix addition" << endl;
	MatrixXd mat1 = mat + mat;
	cout << mat1 << endl;

	cout << "------------" << endl;
	cout << "Matrix multiplication" << endl;
	mat1 = mat*mat;
	cout << mat1 << endl;

	cout << "------------" << endl;
	cout << "Matrix transpose" << endl;
	mat1 = mat.transpose();
	cout << mat1 << endl;

	cout << "------------" << endl;
	cout << "Matrix LU decomposition" << endl;

	PartialPivLU<Matrix<double, 3, 3>> lu(mat);
	
	Matrix<double, 3, 3> l;
	Matrix<double, 3, 3> u;

	l = lu.matrixLU().triangularView<StrictlyLower>();
	l += Matrix<double, 3, 3>::Identity();
	u = lu.matrixLU().triangularView<Upper>();
	
	cout << l << endl;
	cout << u << endl;


	
	cout << "Determinant: " << mat1.determinant() << endl;

	cout << "------------" << endl;
	cout << "Norm: " << mat.norm() <<endl;


	cout << "------------" << endl;
	cout << "Eye matrix" << endl;
	cout << Matrix<double, 3, 3>::Identity() << endl;
	
	/* 
	666 not supported initially
	
	cout << "------------" << endl;
	cout << "Givens Rotation Matrix with theta: " << theta << " i = 1; j = 2" << endl;
	BOViL::math::Matrix<double> mat9 = BOViL::math::createGivenRotation(3, 1, 2, theta);	
	mat9.showMatrix();
	*/

	
	cout << "------------" << endl;
	cout << "Matrix QR decomposition" << endl;
	HouseholderQR<Matrix<double,3,3>> qr(mat);

	Matrix<double, 3, 3> q = qr.householderQ();
	Matrix<double, 3, 3> r = qr.matrixQR().triangularView<Upper>();

	cout << q << endl;
	cout << r << endl;
	
	
	cout << "------------" << endl;
	cout << "Test inverse of: " << endl;
	
	cout << mat.inverse() << endl;
}