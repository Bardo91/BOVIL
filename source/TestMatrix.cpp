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
							7.0, 8.0, 9.0	};

	BOViL::math::Matrix<double> mat1(matArray, 3, 3);
	mat1.showMatrix();

	BOViL::math::Matrix<double> mat2;
	mat2 = mat1;
	mat2.showMatrix();

	BOViL::math::Matrix<double> mat3 = mat1 + mat2;
	mat3.showMatrix();

	//BOViL::math::Matrix<double> mat4 = mat1 * mat2;
	//mat4.showMatrix();

}