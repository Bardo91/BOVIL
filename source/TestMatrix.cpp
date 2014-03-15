/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-12
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "TestMatrix.h"

void testMatrix(){
	std::cout << "TESTING MATRIX OPERATIONS" << std::endl;
	double matArray[9] = {	1.0, 2.0, 3.0, 
							4.0, 5.0, 6.0, 
							7.0, 8.0, 8.0	};
	std::cout << "Matrix creation" << std::endl;
	BOViL::math::Matrix<double> mat1(matArray, 3, 3);
	mat1.showMatrix();

	std::cout << "Matrix asignation" << std::endl;
	BOViL::math::Matrix<double> mat2;
	mat2 = mat1;
	mat2.showMatrix();

	std::cout << "Matrix addition" << std::endl;
	BOViL::math::Matrix<double> mat3 = mat1 + mat2;
	mat3.showMatrix();

	std::cout << "Matrix substraction" << std::endl;
	BOViL::math::Matrix<double> mat4 = mat1 * mat2;
	mat4.showMatrix();

	std::cout << "Matrix transpose" << std::endl;
	BOViL::math::Matrix<double> mat5 = !mat4;
	mat5.showMatrix();

	std::cout << "Matrix LU decomposition" << std::endl;
	BOViL::math::Matrix<double> matL(3, 3), matU(3, 3);
	if(mat1.decompositionLU(matL, matU)){
		matL.showMatrix();
		matU.showMatrix();
	}

	std::cout << "Matrix LU decomposition" << std::endl;
	std::cout << "Determinant: " << ~mat1 << std::endl;

	std::cout << "Norm" << std::endl;
	BOViL::math::Matrix<double> mat6(matArray, 3, 1);	
	mat6.showMatrix();
	std::cout << "Norm: " << mat6.norm() << std::endl;


}