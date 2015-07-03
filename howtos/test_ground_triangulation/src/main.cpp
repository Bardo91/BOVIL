/////////////////////////////////////////////////////////////////////////////////////////
//
//	BOViL: Testing ground triangulation
//
//		Author: Pablo Ramón Soria
//		Date:	2014-05-10
/////////////////////////////////////////////////////////////////////////////////////////

#include <core/math/geometrics/Geometrics.h>

int main(int argc, char** argv){

	BOViL::math::Matrix<double> camOri = BOViL::math::createRotationMatrixEuler(-0.0964, -0.0035, 1.5030);
	
	double arrayPos[3] = { 5.4856, 7.5687, 1.7471 };
	BOViL::math::Matrix<double> camPos(arrayPos, 3, 1);
	
	BOViL::math::Matrix<double> pos = BOViL::math::triangulateFromImageToGround3D(BOViL::Point2ui(328, 400),
		camPos,
		camOri,
		738.143358488352310,
		BOViL::Point2d(346.966835812843040, 240.286986071815390),
		0.069);
	

	pos.showMatrix();

	system("PAUSE");

}