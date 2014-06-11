/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: Assets
//
//		Author: Pablo Ramón Soria
//		Date:	2014-06-11
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "matrix_asserts.h"
#include <cassert>

using namespace BOViL::math;

void matrix_asserts(){

	double mat1_array[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	double mat2_array[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 8 };
	double mat3_array[6] = { 1, 1, 1, 1, 1, 1};


	Matrix<double> mat1(mat1_array, 3, 3);
	Matrix<double> mat2(mat2_array, 3, 3);
	Matrix<double> mat3(mat3_array, 2, 3);


	std::cout << mat1.determinant() << std::endl;
	Matrix<double> L(3,3), U(3,3);
	mat1.decompositionLU(L, U);
	L.showMatrix();
	U.showMatrix();

	assert(mat1.determinant() == 0.0);
	std::cout << "BOViL Matrix Determinant ==> Checked" << std::endl;



	//std::cout << "BOViL Matrix Determinant ==> Checked" << std::endl;


	system("PAUSE");
}