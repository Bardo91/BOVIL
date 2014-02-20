/*
 * SegmentededObject.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: pablo
 */

#include "../../core/types/basicTypes.h"
#include "SegmentedRLEObject.h"

#include <algorithm>    // std::sort
#include <vector>


namespace BIL {
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

		Point SegmentedRLEObject::getUpperLeft() const {
			return upperLeft;
		}

		Point SegmentedRLEObject::getDownRight() const {
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

		Point SegmentedRLEObject::getCentroid() const {
			return Point((upperLeft.x + downRight.x)/2, (upperLeft.y + downRight.y)/2);
		}

		bool sortFunction(LineRLE a, LineRLE b) {
			return a.i < b.i || (a.i == b.i && a.je < b.js) ? true : false;
		}

		void SegmentedRLEObject::sortObj() {
			std::sort(obj.begin(), obj.end(), sortFunction);
		}
	} // namespace segmentation
} // namespace vision

