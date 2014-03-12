/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		OpenBOVIL
//			Author: Pablo Ramon Soria
//			Date:	2014-02-19
/////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _BOVIL_CORE_TYPES_BASICTYPES_H_
#define _BOVIL_CORE_TYPES_BASICTYPES_H_

namespace BOViL{
	//-----------------------------------------------------------------------------
	struct Point{
		// Constructors.
		Point(){ x = 0; y = 0;};
		Point(int _x, int _y){ x = _x; y = _y;};

		// Properties.
		unsigned int x, y;		// Coordinates of the point in the image.
	};

	//-----------------------------------------------------------------------------
	class ImageObject{		// Summarized object.
	public:
		ImageObject(Point _upperLeft, Point _downRight, int _size, int _color){
			centroid = Point((_upperLeft.x + _downRight.x)/2, (_upperLeft.y + _downRight.y)/2);
			width = _downRight.x - _upperLeft.x;
			height = _downRight.y - _upperLeft.y;
			size = _size;
			color = _color;
		};
			
		Point getCentroid() const {return centroid;};
		int getWidth() const {return width;};
		int getHeight() const {return height;};
		int getColor() const {return color;};
	private:
		Point centroid;
		int width, height;
		int color;
		int size;
	};

}	// namespace BOViL


#endif	//_BOVIL_CORE_TYPES_BASICTYPES_H_