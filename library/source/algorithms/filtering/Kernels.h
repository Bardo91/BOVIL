///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	
//	BOVIL: 
//		Author: Pablo Ramón Soria
//		Date:	2015-APR-09
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef BOVIL_ALGORITHMS_FILTERING_KERNELS_H_
#define BOVIL_ALGORITHMS_FILTERING_KERNELS_H_

#include <array>

namespace BOViL{
	namespace algorithms{
		
		template<unsigned Size_>
		using Kernel = std::array<double, Size_ * Size_>;

		typedef Kernel<3> Kernel3;

		const Kernel3 SobelH	= { {	2,	1,	2, 
										0,	0,	0,
										-2,	-1,	-2} };

		const Kernel3 SobelV	= { {	-2, 0, 2,
										-1, 0, 1,
										-2, 0, 2 } };

		const Kernel3 blur		= { {	1.0 / 9, 1.0 / 9, 1.0 / 9,
										1.0 / 9, 1.0 / 9, 1.0 / 9,
										1.0 / 9, 1.0 / 9, 1.0 / 9 }	};
	}	//	namespace algorithms
}	//	namespace BOViL

#endif	//	BOVIL_ALGORITHMS_FILTERING_KERNELS_H_