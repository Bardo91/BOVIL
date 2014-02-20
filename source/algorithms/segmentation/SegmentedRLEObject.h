/////////////////////////////////////////////////////////////////////////////////////////
//		OpenBIL
//			Author: Pablo Ramon Soria
//			Date:	2014-02-19
/////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _OPENBIL_ALGORITHM_SEGMENTATION_H_
#define _OPENBIL_ALGORITHM_SEGMENTATION_H_

#include <vector>
#include "../../core/types/BasicTypes.h"

namespace BIL{
	namespace algorithms{
		//-----------------------------------------------------------------------------
			struct LineRLE{		// RLE encoding object.
				LineRLE(unsigned int _i,
						unsigned int _js,
						unsigned int _je,
						int _color){
							i = _i;
							js = _js;
							je = _je;
							size = je - js;
							color = _color;
							hasParent = false;
							pi = pj = 0;
							iObj = -1;
				};

				unsigned int i;			// Row of the object.
				unsigned int js;		// Started column of the object.
				unsigned int je;		// Ended column of the object.
				unsigned int size;		// Size of the object (= je - js + 1) its computed one time in order to reduce the algorithm operations.

				int color;	// Color of the object.s

				bool hasParent;				// Flag if the RLE was parented.
				unsigned int pi;			// Index of the parent in the vector.
				unsigned int pj;			// Index of the parent in the vector.

				int iObj;

			};

		class SegmentedRLEObject {
			std::vector<LineRLE> obj;

			Point upperLeft, downRight; // Border pixels
			int color;
			unsigned int size;

		public:
			SegmentedRLEObject(LineRLE ini);

			void addLineObjRLE(LineRLE);
			void addRLEFamily(SegmentedRLEObject&);

			int getLines() const;
			LineRLE getRLEObj(int) const;
			Point getUpperLeft() const;
			Point getDownRight() const;
			unsigned int getColor() const;
			unsigned int getSize() const;
			unsigned int getBBSize() const;
			Point getCentroid() const;

			void sortObj();
		};

	}	// namespace algorithms
}	// namespace BIL

#endif	//_OPENBIL_ALGORITHM_SEGMENTATION_H_