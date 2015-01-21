/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: segmentation
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-02-19
//
/////////////////////////////////////////////////////////////////////////////////////////


#include "../../core/types/BasicTypes.h"
#include "SegmentedRLEObject.h"

#include <algorithm>    // std::sort
#include <vector>


namespace BOViL {
	namespace algorithms {
		SegmentedRLEObject::SegmentedRLEObject(LineRLE ini) {
			upperLeft.x = 9999;
			downRight.x = 0;
			upperLeft.y = 9999;
			downRight.y = 0;
			size = 0;
			color = ini.color;
			addLineObjRLE(ini);

		}

		void SegmentedRLEObject::addLineObjRLE(LineRLE aux) {
			obj.push_back(aux);

			if (upperLeft.y > aux.i)
				upperLeft.y = aux.i;
			if (upperLeft.x > aux.js)
				upperLeft.x = aux.js;
			if (downRight.y < aux.i)
				downRight.y = aux.i;
			if (downRight.x < aux.je)
				downRight.x = aux.je;
			size += aux.size + 1;
		}

		void SegmentedRLEObject::addRLEFamily(SegmentedRLEObject& family) {
			for (int k = 0; k < family.getLines(); k++) {
				LineRLE aux = family.getRLEObj(k);
				obj.push_back(aux);
				if (upperLeft.y > aux.i)
					upperLeft.y = aux.i;
				if (upperLeft.x > aux.js)
					upperLeft.x = aux.js;
				if (downRight.y < aux.i)
					downRight.y = aux.i;
				if (downRight.x < aux.je)
					downRight.x = aux.je;
				size += aux.size + 1;
			}
		}

		int SegmentedRLEObject::getLines() const {
			return obj.size();
		}

		LineRLE SegmentedRLEObject::getRLEObj(int k) const {
			return obj[k];
		}

		Vec2ui SegmentedRLEObject::getUpperLeft() const {
			return upperLeft;
		}

		Vec2ui SegmentedRLEObject::getDownRight() const {
			return downRight;
		}

		unsigned int SegmentedRLEObject::getColor() const {
			return color;
		}

		unsigned int SegmentedRLEObject::getSize() const {
			return size;
		}

		unsigned int SegmentedRLEObject::getBBSize() const {
			return (downRight.x - upperLeft.x) * (downRight.y - upperLeft.y);
		}

		Vec2ui SegmentedRLEObject::getCentroid() const {
			return Vec2ui((upperLeft.x + downRight.x)/2, (upperLeft.y + downRight.y)/2);
		}

		bool sortFunction(LineRLE a, LineRLE b) {
			return a.i < b.i || (a.i == b.i && a.je < b.js) ? true : false;
		}

		void SegmentedRLEObject::sortObj() {
			std::sort(obj.begin(), obj.end(), sortFunction);
		}
	} // namespace segmentation
} // namespace BOViL

