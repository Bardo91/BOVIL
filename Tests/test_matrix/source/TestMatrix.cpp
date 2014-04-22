/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-12
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "TestMatrix.h"

void testMatrix(){
	std::cout << "--------- TESTING MATRIX OPERATIONS --------------" << std::endl;
	double matArray[9] = {	1.0, 2.0, 3.0, 
							4.0, 5.0, 6.0, 
							7.0, 8.0, 8.0	};

	std::cout << "Matrix creation" << std::endl;
	BOViL::math::Matrix<double> mat1(matArray, 3, 3);
	mat1.showMatrix();

	std::cout << "------------" << std::endl;
	std::cout << "Matrix asignation" << std::endl;
	BOViL::math::Matrix<double> mat2;
	mat2 = mat1;
	mat2.showMatrix();

	std::cout << "------------" << std::endl;
	std::cout << "Matrix addition" << std::endl;
	BOViL::math::Matrix<double> mat3 = mat1 + mat2;
	mat3.showMatrix();

	std::cout << "------------" << std::endl;
	std::cout << "Matrix multiplication" << std::endl;
	BOViL::math::Matrix<double> mat4 = mat1 * mat3;
	mat4.showMatrix();

	std::cout << "------------" << std::endl;
	std::cout << "Matrix transpose" << std::endl;
	BOViL::math::Matrix<double> mat5 = mat4.transpose();
	mat5.showMatrix();

	std::cout << "------------" << std::endl;
	std::cout << "Matrix LU decomposition" << std::endl;
	BOViL::math::Matrix<double> matL(3, 3), matU(3, 3);
	if(mat1.decompositionLU(matL, matU)){
		matL.showMatrix();
		matU.showMatrix();
	}

	std::cout << "Determinant: " << mat1.determinant() << std::endl;

	std::cout << "------------" << std::endl;
	std::cout << "Norm" << std::endl;
	BOViL::math::Matrix<double> mat6(matArray, 3, 1);	
	mat6.showMatrix();
	std::cout << "Norm: " << mat6.norm() << std::endl;

	std::cout << "------------" << std::endl;
	std::cout << "Eye matrix" << std::endl;
	BOViL::math::Matrix<double> mat7 = BOViL::math::createEye<double>(3);	
	mat7.showMatrix();

	std::cout << "------------" << std::endl;
	std::cout << "Scale Matrix" << std::endl;
	BOViL::math::Matrix<double> mat8 = mat7*0.25;	
	mat8.showMatrix();

	double theta = atan(4.0/6.0);

	std::cout << "------------" << std::endl;
	std::cout << "Givens Rotation Matrix with theta: " << theta << " i = 1; j = 2" << std::endl;
	BOViL::math::Matrix<double> mat9 = BOViL::math::createGivenRotation(3, 1, 2, theta);	
	mat9.showMatrix();

	std::cout << "------------" << std::endl;
	std::cout << "Matrix QR decomposition with Givens Rotation" << std::endl;
	BOViL::math::Matrix<double> matQ(3, 3), matR(3, 3);
	if(mat1.decompositionQR_GR(matQ, matR)){
		matQ.showMatrix();
		matR.showMatrix();

		BOViL::math::Matrix<double> matRes = matQ*matR;
		matRes.showMatrix();
	}
	std::cout << "------------" << std::endl;
	std::cout << "Test inverse of: " << std::endl;
	mat1.showMatrix();
	std::cout << "is: " << std::endl;
	BOViL::math::Matrix<double> matInv = mat1^-1;
	matInv.showMatrix();

	std::cout << "----- TESTING NON SQUARE MATRIX --------" << std::endl;

	std::cout << "------------" << std::endl;
	double array2[6] = {	1.0, 2.0, 3.0,
							4.0, 5.0, 6.0	};

	BOViL::math::Matrix<double> mat10(array2, 2, 3);
	mat10.showMatrix();

	std::cout << "------------" << std::endl;
	std::cout << "Transpose NS matrix" << std::endl;
	BOViL::math::Matrix<double> mat11 = mat10.transpose();
	mat11.showMatrix();

	std::cout << "------------" << std::endl;
	std::cout << "Multiply NS matrixes" << std::endl;
	BOViL::math::Matrix<double> mat12 = mat10*mat11;
	mat12.showMatrix();

	std::cout << "------------" << std::endl;
	std::cout << "Multiply NS matrix" << std::endl;
	BOViL::math::Matrix<double> mat13 = mat11*mat10;
	mat13.showMatrix();

	
}