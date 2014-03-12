/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-05-03
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "ColorClusterSpace.h"


namespace BOViL{
	ColorClusterSpace::ColorClusterSpace(	int n, 
												unsigned char*_AClass, 
												unsigned char* _BClass,	
												unsigned char* _CClass, 
												const c3u *_colors) {
			AClass = new unsigned char[n];
			BClass = new unsigned char[n];
			CClass = new unsigned char[n];
			clusters = new c3u[8];
			size = n;

			for (int i = 0; i < n; i++) {
				AClass[i] = _AClass[i];
				BClass[i] = _BClass[i];
				CClass[i] = _CClass[i];
				if (i < 8)
					clusters[i] = _colors[i];
			}
		}

		ColorClusterSpace::~ColorClusterSpace() {
			/*delete[] AClass;
			delete[] BClass;
			delete[] CClass;
			delete[] clusters;*/

		}

<<<<<<< HEAD
}	// namespace BOVIL
=======
}	// namespace BOViL
>>>>>>> 2b981b1b56e27612f9bbd1398f52973083f4eef0
